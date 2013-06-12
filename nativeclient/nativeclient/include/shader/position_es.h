#include <string>

namespace Natorium
{

/*const std::string strPositionVertex(
	"#version 330\n"
	"\n"
	"\n"
	"layout(std140) uniform GlobalMatrices\n"
	"{\n"
	"    mat4 cameraToClip;\n"
	"    mat4 worldToCamera;\n"
	"};\n"
	"\n"
	"uniform mat4 modelToWorld;\n"
	"\n"
	"layout(location = 0) in vec4 position;\n"
	"layout(location = 1) in vec4 color;\n"
	"\n"
	"smooth out vec4 fragmentColor;\n"
	"\n"
	"void main()\n"
	"{\n"
	"	vec4 temp = modelToWorld * position;\n"
	"	temp = worldToCamera * temp;\n"
	"	gl_Position = cameraToClip * temp;\n"
	"	//gl_Position = position;\n"
	"	fragmentColor = color;\n"
	"}\n"
);*/

const std::string strPositionVertex(
	"#version 100\n"
	"\n"
	"\n"
	"uniform mat4 projection;\n"
	"uniform mat4 view;\n"
	"uniform mat4 model;\n"
	"\n"
	"attribute vec4 position;\n"
	"attribute vec4 color;\n"
	"\n"
	"varying vec4 fragmentColor;\n"
	"\n"
	"void main()\n"
	"{\n"
	"	gl_Position = projection * view * model * position;\n"
	"	//gl_Position = vec4(0.5);\n"
	"	fragmentColor = color;\n"
	"}\n"
);


const std::string strPositionFragment(
	"#version 100\n"
	"\n"
	"precision mediump float;\n"
	"varying vec4 fragmentColor;\n"
	"\n"
	"void main()\n"
	"{\n"
	"	gl_FragColor = fragmentColor;\n"
	"}\n"
);

}