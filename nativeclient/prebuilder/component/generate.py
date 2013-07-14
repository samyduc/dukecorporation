import xml.etree.cElementTree as ET


CONST_DO_NOT_GENERATE = ['Component', 'Shape', 'Input', 'b2ContactListener']

class Writer:

	def __init__(self, name, header_path, xml_path, cpp_path, version, src_class, properties):

		self.name = name
		self.xml_path = xml_path
		self.cpp_path = cpp_path
		self.version = version

		self.properties = properties
		self.src_class = src_class

		# find include path
		index = header_path.find("component")
		self.include_string = header_path[index:]
		self.include_string = self.include_string.replace('\\', '/')

	def run(self):

		if self.name not in CONST_DO_NOT_GENERATE:
			self.write_xml()
			self.write_cpp()

	def write_xml(self):

		root = ET.Element("component")
		root.set("class", self.name)
		root.set("version", str(self.version))

		for class_property in self.properties:
			xml_property = ET.SubElement(root, "property")
			xml_property.set("type", class_property['type'])
			xml_property.set("name", class_property['name'])
			xml_property.set("value", str(0))

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
		cpp_file.write('	if(_type == 0)\n')
		cpp_file.write('	{\n')
		cpp_file.write("		component = _entity->AddComponent<%s>();\n" % (self.name))
		cpp_file.write('	}\n')
		cpp_file.write('	else\n')
		cpp_file.write('	{\n')
		cpp_file.write("		component = static_cast<%s*>(_entity->GetComponentByType(_type));\n" % (self.name))		
		cpp_file.write('	}\n')
		cpp_file.write("\n")


		# call mother class
		for inherit_class in self.src_class['inherits']:
			if inherit_class['class'] not in CONST_DO_NOT_GENERATE:
				cpp_file.write("	%s::Clone(_entity, %s::GetType());\n" % (inherit_class['class'], self.name))

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