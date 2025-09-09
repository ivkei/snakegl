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

void SnakeRenderer::Render(Field& field){
  SGE::TSRenderer::Instance()->Clear(field.UnitDividerColor());

  //Field & cells
  for (int i = 0; i < field.Width(); ++i){
    for (int j = 0; j < field.Height(); ++j){
      SGE::TSRenderer::Instance()->Quad(glm::vec2(i + field.UnitHorOffset(), j + field.UnitVerOffset()), glm::vec2(field.UnitWidth(), field.UnitHeight()), field.SlotColor(i, j));
    }
  }

  SGE::TSRenderer::Instance()->Render();
}
