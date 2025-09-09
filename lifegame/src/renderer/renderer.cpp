#include"renderer.h"

#include"glm/gtc/matrix_transform.hpp"
#include"sge.h"

void SnakeRenderer::SetupShadersAndCoord(Field& field){
  glm::mat4 proj = glm::ortho(0.0f, (float)field.Width(), 0.0f, (float)field.Height(), -1.0f, 1.0f);

  std::filesystem::path execDir = SGE::GetExecDir();

  SGE_LOG_INFO("Exec dir: ", execDir.string());

  SGE::TSRenderer::Instance()->FragShader((execDir / RES_DIR / "shaders/fragP.glsl").string().c_str(), true); //Indirect because windows likes to return wchar* instead of char*
  SGE::TSRenderer::Instance()->VertShader((execDir / RES_DIR / "shaders/vertP.glsl").string().c_str(), true);
  SGE::TSRenderer::Instance()->Uniform("uProj", proj);

  SGE_LOG_INFO("Shader dir: ", (execDir / RES_DIR / "shaders"));
}

void SnakeRenderer::Render(Snake& snake, Field& field, AppleManager& appleManager){
  SGE::TSRenderer::Instance()->Clear(field.UnitDividerColor());

  //Field
  for (int i = 0; i < field.Width(); ++i){
    for (int j = 0; j < field.Height(); ++j){
      SGE::TSRenderer::Instance()->Quad(glm::vec2(i + field.UnitHorOffset(), j + field.UnitVerOffset()), glm::vec2(field.UnitWidth(), field.UnitHeight()), field.BackgroundColor());
    }
  }

  //Head
  SnakeHead head = snake.GetHead();
  SGE::TSRenderer::Instance()->Quad(glm::vec2(head.pos.x + field.UnitHorOffset(), head.pos.y + field.UnitVerOffset()), glm::vec2(field.UnitWidth(), field.UnitHeight()), snake.HeadColor());
  //Body
  std::vector<SnakeUnit> body = snake.GetBody();
  for (int i = 0; i < body.size(); ++i){
    SGE::TSRenderer::Instance()->Quad(glm::vec2(body[i].pos.x + field.UnitHorOffset(), body[i].pos.y + field.UnitVerOffset()), glm::vec2(field.UnitWidth(), field.UnitHeight()), body[i].color);
  }

  std::vector<Apple> apples = appleManager.GetApples();
  for (int i = 0; i < apples.size(); ++i){
    SGE::TSRenderer::Instance()->Quad(glm::vec2(apples[i].pos.x + field.UnitHorOffset(), apples[i].pos.y + field.UnitVerOffset()), glm::vec2(field.UnitWidth(), field.UnitHeight()), appleManager.AppleColor());
  }

  SGE::TSRenderer::Instance()->Render();
}
