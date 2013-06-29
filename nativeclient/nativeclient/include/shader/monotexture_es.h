#include <string>

namespace Natorium
{

const std::string strMonoTextureVertex(
	"#version 100\n"
	"\n"
	"\n"
	"uniform mat4 projection;\n"
	"uniform mat4 view;\n"
	"uniform mat4 model;\n"
	"\n"
	"\n"
	"\n"
	"attribute vec4 position;\n"
	"attribute vec4 color;\n"
	"attribute vec2 texCoord;\n"
	"\n"
	"varying vec4 fragmentColor;\n"
	"varying vec2 baseTexCoord;\n"
	"\n"
	"void main()\n"
	"{\n"
	"	gl_Position = projection * view * model * position;\n"
	"\n"
	"	fragmentColor = color;\n"
	"	baseTexCoord = texCoord;\n"
	"}\n"
);

const std::string strMonoTextureFragment(
	"#version 100\n"
	"\n"
	"precision mediump float;\n"
	"varying vec2 baseTexCoord;\n"
	"varying vec4 fragmentColor;\n"
	"uniform sampler2D baseTexture;\n"
	"\n"
	"\n"
	"void main()\n"
	"{\n"
	"\n"
	"	gl_FragColor = fragmentColor * texture2D(baseTexture, baseTexCoord);\n"
	"}\n"
);

}