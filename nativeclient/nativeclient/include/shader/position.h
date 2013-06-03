#include <string>

namespace Natorium
{

const std::string strPositionVertex(
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
);


const std::string strPositionFragment(
	"#version 330\n"
	"\n"
	"\n"
	"smooth in vec4 fragmentColor;\n"
	"out vec4 outputColor;\n"
	"\n"
	"void main()\n"
	"{\n"
	"	outputColor = fragmentColor;\n"
	"}\n"
);

}