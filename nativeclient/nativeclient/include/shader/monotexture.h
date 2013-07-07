#include <string>

namespace Natorium
{

const std::string strMonoTextureVertex(
	"#version 330\n"
	"\n"
	"\n"
	"uniform mat4 projection;\n"
	"uniform mat4 view;\n"
	"uniform mat4 model;\n"
	"\n"
	"\n"
	"\n"
	"layout(location = 0) in vec4 position;\n"
	"layout(location = 1) in vec4 color;\n"
	"layout(location = 2) in vec2 texCoord;\n"
	"\n"
	"smooth out vec4 fragmentColor;\n"
	"smooth out vec2 baseTexCoord;\n"
	"\n"
	"void main()\n"
	"{\n"
	"	gl_Position = projection * view * model * position;\n"
	/*"	gl_Position = position;\n"*/
	"\n"
	"	fragmentColor = color;\n"
	"	baseTexCoord = texCoord;\n"
	"}\n"
);

const std::string strMonoTextureFragment(
	"#version 330\n"
	"\n"
	"\n"
	"smooth in vec2 baseTexCoord;\n"
	"smooth in vec4 fragmentColor;\n"
	"uniform sampler2D baseTexture;\n"
	"\n"
	"out vec4 outputColor;\n"
	"\n"
	"void main()\n"
	"{\n"
	"\n"
	"	outputColor = fragmentColor * texture(baseTexture, baseTexCoord);\n"
	"}\n"
);

}