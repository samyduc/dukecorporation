import os
import sys

import CppHeaderParser
import binascii
from xml.dom.minidom import parse, parseString

from generate import Writer

CONST_COMPONENT_SRC = "include/component/"
CONST_COMPONENT_GENERATED = "source/component/generated/"
CONST_COMPONENT_GENERATED_DESC = "data/component/"
CONST_PREFIX_GENERATED = "gen_"



class Generator:

	def __init__(self, base_path):

		self.base_path = base_path

	def run(self):
		
		component_path = os.path.join(self.base_path, CONST_COMPONENT_SRC)

		for root, subFolders, files in os.walk(component_path):

			print("In folder %s" % (root))

			for filename in files:
				path = os.path.join(root, filename)
				print("Parsing %s" % (path))
				parser = Parser(self.base_path, path, filename)
				parser.run()

class Parser:


	def __init__(self, base_path, header_path, filename):
		"""
		Parse header to generate a component template

		"""

		dummy, self.fileextension = os.path.splitext(header_path)
		self.filename = os.path.basename(header_path)[:-1*len(self.fileextension)]
		self.path_src = header_path

		self.path_gen = os.path.join(base_path, CONST_COMPONENT_GENERATED, CONST_PREFIX_GENERATED + self.filename + ".cpp")
		self.path_desc = os.path.join(base_path, CONST_COMPONENT_GENERATED_DESC, self.filename + ".xml")

		print("	path_src %s" % (self.path_src))
		print("	path_gen %s" % (self.path_gen))
		print("	path_desc %s" % (self.path_desc))

	def run(self):

		if self.fileextension == ".h":
			src = open(self.path_src, 'rb')
			data = src.read()
			src.close()

			crc_src = long(binascii.crc32(data))

			if not self.check_version(crc_src):
				classes_properties = self.parse_src()

				# take the first one
				class_name, src_class, class_properties = classes_properties[0]

				if len(classes_properties) > 1:
					print("illegal to have more than one component in a header")
					exit(-1)

				writer = Writer(class_name, self.path_src, self.path_desc, self.path_gen, crc_src, src_class, class_properties)
				writer.run()

	def check_version(self, crc_src):

		crc_desc = 0

		try:
			dom = parse(self.path_desc)
			element = dom.getElementsByTagName("component")[0]
			crc_desc = long(element.attributes["version"].value)
			 
		except IOError:
			print("		Desc file does not exist %s" % (self.path_desc))

		print("		Src version %u | Desc version %u" % (crc_src, crc_desc))
		return crc_desc == crc_src

	def parse_src(self):

		cppHeader = CppHeaderParser.CppHeader(self.path_src)

		class_properties = []

		# only one class usualy
		for name_class, src_class in cppHeader.classes.iteritems():

			for inherit_class in src_class['inherits']:

				if inherit_class['class']:

					# start real parsing here
					print("		Component found %s" % (name_class))
					properties = src_class["properties"]["public"]
					class_properties.append((name_class, src_class, properties))
					break

		return class_properties







