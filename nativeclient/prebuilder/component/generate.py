import xml.etree.cElementTree as ET

# ugly
CONST_DO_NOT_GENERATE = ['Component', 'Shape', 'Input', 'b2ContactListener']

class Writer:

	def __init__(self, parser, components):

		self.name = parser.class_name
		self.xml_path = parser.path_desc
		self.cpp_path = parser.path_gen
		self.version = parser.crc_src

		self.properties = parser.classes_properties[0][2]
		self.src_class = parser.classes_properties[0][1]

		# find include path
		index = parser.path_src.find("component")
		self.include_string = parser.path_src[index:]
		self.include_string = self.include_string.replace('\\', '/')

		self.components = components
		self.parser = parser
		self.parser.include_string = self.include_string

	def run(self):

		self.write_xml()
		self.write_cpp()

	def write_xml_property(self, root, parser, components):
		"""
		Recursive hell

		"""

		for inherit_class in parser.classes_properties[0][1]['inherits']:
			if inherit_class['class'] not in CONST_DO_NOT_GENERATE:

				self.write_xml_property(root, self.components[inherit_class['class']], components)

		for class_property in parser.classes_properties[0][2]:
			xml_property = ET.SubElement(root, "property")
			xml_property.set("type", class_property['type'])
			xml_property.set("name", class_property['name'])
			xml_property.set("value", str(0))

	def write_xml(self):

		root = ET.Element("component")
		root.set("class", self.name)
		root.set("version", str(self.version))

		self.write_xml_property(root, self.parser, self.components)

		tree = ET.ElementTree(root)
		tree.write(self.xml_path)

	def write_cpp(self):

		cpp_file = open(self.cpp_path, 'w')

		cpp_file.write("// Generated file : do not edit manually \n")
		cpp_file.write("\n")
		cpp_file.write("\n")
		cpp_file.write('#include "%s"\n' % (self.include_string))
		cpp_file.write("\n")
		cpp_file.write('#include "base/component.h"\n')
		cpp_file.write('#include "base/entity.h"\n')
		cpp_file.write('#include "base/serializer.h"\n')
		cpp_file.write("\n")
		cpp_file.write("\n")
		cpp_file.write("\n")
		cpp_file.write('namespace Natorium\n')
		cpp_file.write('{\n')
		cpp_file.write("\n")

		# Clone
		cpp_file.write("\n")
		self.write_clone(cpp_file)
		cpp_file.write("\n")

		# serialization
		cpp_file.write("\n")
		self.write_serialization(cpp_file)
		cpp_file.write("\n")

		cpp_file.write("\n")
		cpp_file.write("\n")
		cpp_file.write('}\n')

		cpp_file.close()


	def write_clone(self, cpp_file):

		cpp_file.write("void %s::Clone(Entity* _entity, natU32 _type) const\n" % (self.name))
		cpp_file.write('{\n')
		cpp_file.write("	%s* component;\n" % (self.name))
		cpp_file.write("	natU32 base_type = %s::GetType();\n" % (self.name))
		cpp_file.write('	if(_type == 0)\n')
		cpp_file.write('	{\n')
		cpp_file.write("		component = _entity->AddComponent<%s>();\n" % (self.name))
		cpp_file.write('	}\n')
		cpp_file.write('	else\n')
		cpp_file.write('	{\n')
		cpp_file.write("		component = static_cast<%s*>(_entity->GetComponentByType(_type));\n" % (self.name))	
		cpp_file.write('		base_type = _type;\n')
		cpp_file.write('	}\n')
		cpp_file.write("\n")


		from parse import CONST_DO_NOT_GENERATE

		# call mother class
		for inherit_class in self.src_class['inherits']:
			if inherit_class['class'] not in CONST_DO_NOT_GENERATE:
				cpp_file.write("	%s::Clone(_entity, base_type);\n" % (inherit_class['class']))

		for class_property in self.properties:
			cpp_file.write('	component->%s = %s;\n' % (class_property['name'], class_property['name']))

		cpp_file.write('}\n')

	def write_serialization(self, cpp_file):

		cpp_file.write("void %s::WriteData(Serializer& _ser)\n" % (self.name))
		cpp_file.write('{\n')

		for inherit_class in self.src_class['inherits']:
			if inherit_class['class'] not in CONST_DO_NOT_GENERATE:
				cpp_file.write("	%s::WriteData(_ser);\n" % (inherit_class['class']))

		for class_property in self.properties:
			if class_property['type'][-1] == "*":
				cpp_file.write('	_ser << reinterpret_cast<void**>(&%s);\n' % (class_property['name']))
			else:
				cpp_file.write('	_ser << %s;\n' % (class_property['name']))

		cpp_file.write('}\n')

		cpp_file.write("\n")
		cpp_file.write("\n")

		cpp_file.write("void %s::ReadData(Serializer& _ser)\n" % (self.name))
		cpp_file.write('{\n')

		for inherit_class in self.src_class['inherits']:
			if inherit_class['class'] not in CONST_DO_NOT_GENERATE:
				cpp_file.write("	%s::ReadData(_ser);\n" % (inherit_class['class']))

		for class_property in self.properties:
			if class_property['type'][-1] == "*":
				cpp_file.write('	_ser >> reinterpret_cast<void**>(&%s);\n' % (class_property['name']))
			else:
				cpp_file.write('	_ser >> %s;\n' % (class_property['name']))

		cpp_file.write('}\n')