#include"debug.h"

#include"GL/glew.h"

#include"logger.h"

void GLClearErrors(){
  while (glGetError());
}

void GLLogErrors(const char* name, const char* file, int line){
  while (GLenum error = glGetError()){
    SGE_LOG_ERROR("[OpenGL Error]: ", std::hex, error, std::dec, "\nName: ", name, "\nFile: ", file, "\nLine: ", line);
  }
}

static const char* GLSourceToString(GLenum source){
  switch (source) {
    case GL_DEBUG_SOURCE_API:
    return "API";

    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
    return "WINDOW SYSTEM";

    case GL_DEBUG_SOURCE_SHADER_COMPILER:
    return "SHADER COMPILER";

    case GL_DEBUG_SOURCE_THIRD_PARTY:
    return "THIRD PARTY";

    case GL_DEBUG_SOURCE_APPLICATION:
    return "APPLICATION";

    case GL_DEBUG_SOURCE_OTHER:
    return "UNKNOWN";

    default:
    return "UNKNOWN";
  }
}

static const char* GLTypeToString(GLenum type){
  switch (type) {
    case GL_DEBUG_TYPE_ERROR:
    return "ERROR";

    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
    return "DEPRECATED BEHAVIOR";

    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
    return "UDEFINED BEHAVIOR";

    case GL_DEBUG_TYPE_PORTABILITY:
    return "PORTABILITY";

    case GL_DEBUG_TYPE_PERFORMANCE:
    return "PERFORMANCE";

    case GL_DEBUG_TYPE_OTHER:
    return "OTHER";

    case GL_DEBUG_TYPE_MARKER:
    return "MARKER";

    default:
    return "UNKNOWN";
  }
}

static const char* GLSeverityToString(GLenum severity){
  switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
    return "HIGH";

    case GL_DEBUG_SEVERITY_MEDIUM:
    return "MEDIUM";

    case GL_DEBUG_SEVERITY_LOW:
    return "LOW";

    case GL_DEBUG_SEVERITY_NOTIFICATION:
    return "NOTIFICATION";

    default:
    return "UNKNOWN";
  }
}

static void GLDebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                            const GLchar* msg, const void* data){
  const char* sourceStr = GLSourceToString(source);
  const char* typeStr = GLTypeToString(type);
  const char* severityStr = GLSeverityToString(severity);

  SGE_LOG_INFO(id, ": ", typeStr, " of ", severityStr, ", raised from ", sourceStr, ": ", msg);
}

void GLEnableAutoLogging(){
  //Add error handling
  glEnable(GL_DEBUG_OUTPUT); //Driver now has access to provide textual stuff to application
  glDebugMessageCallback(GLDebugMessageCallback, NULL);
}

