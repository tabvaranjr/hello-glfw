#include "Demo.h"

#include <format.h>

#include "File.h"
#include "Shader.h"

std::shared_ptr<ShaderProgram> makeShaderProgram(const std::string& program)
{
    auto vertexShaderFile = File::readTextFile(fmt::format("shaders/{0}.vert", program));
    Shader vs(Shader::Type::Vertex, vertexShaderFile);

    auto geometryShaderFile = File::readTextFile(fmt::format("shaders/{0}.geom", program));
    Shader gs(Shader::Type::Geometry, geometryShaderFile);

    auto fragmentShaderFile = File::readTextFile(fmt::format("shaders/{0}.frag", program));
    Shader fs(Shader::Type::Fragment, fragmentShaderFile);

    return std::make_shared<ShaderProgram>(vs, gs, fs);
}

std::shared_ptr<Mesh> makeQuad()
{
    return std::make_shared<Mesh>();
}
