#include"src/pch/pch.h"

#include"renderer.h"

#include"GL/glew.h"

#include"include/sge/sge.h"
#include"gl_utils/debug/debug.h"
#include"logger.h"
#include"gl_utils/vertexbufferlayout.h"
#include"gl_utils/vertexarray/vertexarray.h"
#include"gl_utils/shader/shader.h"

#include"darray.h"

#define PI 3.141592653589793115997963468544185161590576171875

namespace SGE{

struct Vertex{
  glm::vec2 pos;
  glm::vec4 color;
};

//Batch
static darray<Vertex> vertexBuffer;
static darray<unsigned int> indexBuffer;

//State info
static bool wasGlewInit = false;
//Ptr because managed lifetime
static VertexArray* pVao;
static int maxVertexCount = 0;
static int maxIndexCount = 0;
static unsigned int vboID;
static unsigned int iboID;
static bool doClear = false;
//Ptr because managed lifetime
static Shader* pShader;

//Index of most bottom left vector
static int BottomLeft(glm::vec2 quad[4]){
  int leastCoordsIndex = 0;
  glm::vec2 currentLeast = quad[0];

  for (int i = 1; i < 4; ++i){
    if ((currentLeast.x > quad[i].x && currentLeast.y >= quad[i].y) || (currentLeast.x >= quad[i].x && currentLeast.y > quad[i].y)){
      currentLeast = quad[i];
      leastCoordsIndex = 1;
    }
  }

  return leastCoordsIndex;
}

static void PushQuad(glm::vec2 vertexPos0, glm::vec2 vertexPos1, glm::vec2 vertexPos2, glm::vec2 vertexPos3,
                     glm::vec4 vertexColor0, glm::vec4 vertexColor1, glm::vec4 vertexColor2, glm::vec4 vertexColor3){
  int offset = vertexBuffer.length();

  //Vertex buffer
  vertexBuffer.emplace_back(vertexPos0, vertexColor0);
  vertexBuffer.emplace_back(vertexPos1, vertexColor1);
  vertexBuffer.emplace_back(vertexPos2, vertexColor2);
  vertexBuffer.emplace_back(vertexPos3, vertexColor3);

  //Index buffer
  glm::vec2 quad[] = {vertexPos0, vertexPos1, vertexPos2, vertexPos3};
  int bottomLeftIndex = BottomLeft(quad);

  indexBuffer.push_back(bottomLeftIndex + offset);
  indexBuffer.push_back((bottomLeftIndex + 1) % 4 + offset);
  indexBuffer.push_back((bottomLeftIndex + 2) % 4 + offset);

  indexBuffer.push_back((bottomLeftIndex + 3) % 4 + offset);
  indexBuffer.push_back((bottomLeftIndex + 1) % 4 + offset);
  indexBuffer.push_back((bottomLeftIndex + 2) % 4 + offset);
}

static void PushTrig(glm::vec2 vertexPos0, glm::vec2 vertexPos1, glm::vec2 vertexPos2,
                     glm::vec4 vertexColor0, glm::vec4 vertexColor1, glm::vec4 vertexColor2){
  int offset = vertexBuffer.length();

  //Vertex buffer
  vertexBuffer.emplace_back(vertexPos0, vertexColor0);
  vertexBuffer.emplace_back(vertexPos1, vertexColor1);
  vertexBuffer.emplace_back(vertexPos2, vertexColor2);

  //Index buffer
  indexBuffer.push_back(0 + offset);
  indexBuffer.push_back(1 + offset);
  indexBuffer.push_back(2 + offset);
}

//Returns -1 vector if rads are greater than 2*PI or less than 0
glm::vec4 RadsToColor(float rads){
  glm::vec4 red =   {1, 0, 0, 1};
  glm::vec4 green = {0, 1, 0, 1};
  glm::vec4 blue =  {0, 0, 1, 1};

  if (rads < PI*3.0f/4.0f && rads >= 0.0f) return glm::mix(red, green, rads*4.0f/3.0f/PI);

  if (rads < PI*4.0f/3.0f && rads >= PI*3.0f/4.0f) return glm::mix(green, blue, (rads*12.0f - 9.0f*PI) / (7.0f*PI));

  if (rads >= PI*4.0f/3.0f && rads <= 2.0f*PI) return glm::mix(blue, red, (rads*3.0f - 4.0f*PI) / (2.0f*PI));

  return glm::vec4(-1);
}

static void PushCircle(glm::vec2 pos, float r, int vertexCount, bool isRainbow, glm::vec4 centerColor = glm::vec4(1), glm::vec4 circColor = glm::vec4(1)){
  int offset = vertexBuffer.length();

  //Vertex buffer
  vertexBuffer.emplace_back(pos, glm::vec4(isRainbow ? glm::vec4(1) : centerColor));

  float vertexEveryRads = 2*PI / vertexCount;
  for (int i = 0; i < vertexCount; ++i){
    glm::vec2 vertexPos = {cos(vertexEveryRads * i) * r + pos.x, sin(vertexEveryRads * i) * r + pos.y};
    glm::vec4 vertexColor = isRainbow ? RadsToColor(vertexEveryRads * i) : circColor;
    vertexBuffer.emplace_back(vertexPos, vertexColor);
  }

  //Index buffer
  for (int i = 0; i < vertexCount; ++i){
    indexBuffer.emplace_back(0 + offset); //Center

    indexBuffer.emplace_back((1 + i) + offset); //Generated dot at circumference

    indexBuffer.emplace_back((i == vertexCount - 1 ? (1) : (2 + i)) + offset); //Another dot that connects to another poly
  }
}

Renderer::Renderer(){
  //Init glew, after make context
  if (!wasGlewInit){
    wasGlewInit = true;
    auto err = glewInit();
    if (err != GLEW_OK){
      SGE_LOG_ERROR("Failed to init glew: ", glewGetErrorString(err));
    }
  }

  //Add error handling
  GLEnableAutoLogging();

  //Set blending
  //                 Take the alpha Find difference between in and one
  GLCall(glBlendFunc(GL_SRC_ALPHA,  GL_ONE_MINUS_SRC_ALPHA));
  GLCall(glEnable(GL_BLEND));

  //Layout
  VertexBufferLayout layout;
  layout.Push<float>(2);
  layout.Push<float>(4);

  //Buffers
  GLCall(glGenBuffers(1, &vboID));
  GLCall(glGenBuffers(1, &iboID));

  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, vboID));

  //Init size of buffers, they still can scale every frame
  GLCall(glBufferData(GL_ARRAY_BUFFER, 10000 * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW));
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 10000 * sizeof(unsigned int), nullptr, GL_DYNAMIC_DRAW));
  maxIndexCount = 10000;
  maxVertexCount = 10000;

  //Vertex Array
  pVao = new VertexArray();
  pVao->Bind();
  pVao->AddLayout(layout);

  //Shader
  pShader = new Shader();
}

Renderer::~Renderer(){
  GLCall(glDeleteBuffers(1, &vboID));
  GLCall(glDeleteBuffers(1, &iboID));

  delete pShader;
  delete pVao;
}

void Renderer::Render(){
  //Render
  if (doClear){
    glClear(GL_COLOR_BUFFER_BIT);
  }

  SGE_LOG_ASSERT(pShader->IsValid(), "Shader is invalid and isnt set, specify fragment and vertex shader please!");
  pShader->Bind();
  pVao->Bind();

  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, vboID));

  //Dont realloc if not needed
  if (vertexBuffer.length() <= maxVertexCount){
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, vertexBuffer.length() * sizeof(Vertex), vertexBuffer.data()));
  }
  else{
    GLCall(glBufferData(GL_ARRAY_BUFFER, vertexBuffer.length() * sizeof(Vertex), vertexBuffer.data(), GL_DYNAMIC_DRAW));
  }

  if (indexBuffer.length() <= maxIndexCount){
    GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indexBuffer.length() * sizeof(unsigned int), indexBuffer.data()));
  }
  else{
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.length() * sizeof(unsigned int), indexBuffer.data(), GL_DYNAMIC_DRAW));
  }

  if (indexBuffer.length() > 2){
    glDrawElements(GL_TRIANGLES, indexBuffer.length(), GL_UNSIGNED_INT, nullptr);
  }

  //Prepare for next batch
  glClearColor(0, 0, 0, 1);
  doClear = false;

  maxVertexCount = std::max(maxVertexCount, (int)vertexBuffer.length());
  maxIndexCount = std::max(maxIndexCount, (int)indexBuffer.length());

  vertexBuffer.clear();
  indexBuffer.clear();
}

void Renderer::Quad(glm::vec2 pos, glm::vec2 dimensions, glm::vec4 color){
  PushQuad(pos, glm::vec2(pos.x + dimensions.x, pos.y), glm::vec2(pos.x, pos.y + dimensions.y), pos + dimensions,
           color, color, color, color);
}

void Renderer::Quad(glm::vec2 vertexPos0, glm::vec2 vertexPos1, glm::vec2 vertexPos2, glm::vec2 vertexPos3,
            glm::vec4 vertexColor0, glm::vec4 vertexColor1, glm::vec4 vertexColor2, glm::vec4 vertexColor3){
  PushQuad(vertexPos0, vertexPos1, vertexPos2, vertexPos3,
           vertexColor0, vertexColor1, vertexColor2, vertexColor3);
}

void Renderer::Trig(glm::vec2 pos, glm::vec2 dimensions, glm::vec4 color){
  PushTrig(pos, glm::vec2(pos.x + dimensions.x, pos.y), glm::vec2(pos.x, pos.y + dimensions.y),
           color, color, color);
}

void Renderer::Trig(glm::vec2 vertexPos0, glm::vec2 vertexPos1, glm::vec2 vertexPos2,
            glm::vec4 vertexColor0, glm::vec4 vertexColor1, glm::vec4 vertexColor2){
  PushTrig(vertexPos0, vertexPos1, vertexPos2,
           vertexColor0, vertexColor1, vertexColor2);
}

void Renderer::Circle(glm::vec2 pos, float r, int vertices, glm::vec4 color){
  PushCircle(pos, r, vertices, false, color, color);
}

void Renderer::Circle(glm::vec2 pos, float r, int vertices, glm::vec4 centerColor, glm::vec4 circumferenceColor){
  PushCircle(pos, r, vertices, false, centerColor, circumferenceColor);
}

void Renderer::Circle(glm::vec2 pos, float r, int vertices, bool isRainbow){
  PushCircle(pos, r, vertices, true);
}

void Renderer::FragShader(const char* string, bool isPath){
  pShader->Frag(string, isPath);
}

void Renderer::VertShader(const char* string, bool isPath){
  pShader->Vert(string, isPath);
}

const char* Renderer::DefaultFragShader = 
"#version 330 core"
"layout(location = 0) out vec4 oCol;"
"void main(){"
"  oCol = vec4(1, 1, 1, 1);"
"}"
;
const char* Renderer::DefaultVertShader =
"#version 330 core"
"layout(location = 0) in vec4 iPos;"
"void main(){"
" gl_Position = iPos;"
"}"
;

void Renderer::Uniform(const char* name, int i){
  pShader->SetUniform(name, i);
}

void Renderer::Uniform(const char* name, float f){
  pShader->SetUniform(name, f);
}

void Renderer::Uniform(const char* name, glm::mat4 m){
  pShader->SetUniform(name, m);
}

void Renderer::Clear(glm::vec4 color){
  glClearColor(color.r, color.g, color.b, color.a);
  doClear = true;
  vertexBuffer.clear();
  indexBuffer.clear();
}

}
