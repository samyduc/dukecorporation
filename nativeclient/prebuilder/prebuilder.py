
import component.parse




CONST_PATH = "../nativeclient/"




if __name__ == "__main__":
	
	generator = component.parse.Generator(CONST_PATH)
	generator.run()