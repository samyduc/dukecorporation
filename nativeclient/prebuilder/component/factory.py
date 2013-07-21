

CONST_COMPONENT_FACTORY = "component/componentfactory.h"


class Writer:

	def __init__(self, name, cpp_path, components):

		self.name = name
		self.cpp_path = cpp_path
		self.components = components

	def run(self):
		self.write_factory()

	def write_factory(self):

		cpp_file = open(self.cpp_path, 'w')

		cpp_file.write("// Generated file : do not edit manually \n")
		cpp_file.write("\n")
		cpp_file.write("\n")
		cpp_file.write('#include "%s"\n' % (CONST_COMPONENT_FACTORY))
		cpp_file.write("\n")
		cpp_file.write('#include "base/component.h"\n')
		cpp_file.write('#include "base/entity.h"\n')
		cpp_file.write('#include "base/serializer.h"\n')
		cpp_file.write("\n")

		for component_name, component_include in self.components.iteritems():
			cpp_file.write('#include "%s"\n' % (component_include.include_string))

		cpp_file.write("\n")
		cpp_file.write("\n")
		cpp_file.write('namespace Natorium\n')
		cpp_file.write('{\n')
		cpp_file.write("\n")
		cpp_file.write("void %s::PopulateFactory()\n" % (self.name))
		cpp_file.write('{\n')

		for component_name, component_include in self.components.iteritems():
			cpp_file.write("	m_componentFactory[%s::GetType()] = new %s();\n" % (component_name, component_name))

		cpp_file.write('}\n')
		cpp_file.write("\n")
		cpp_file.write('}\n')