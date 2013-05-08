import player

class World:


	def __init__(self, size_x, size_y):
		self.players = {}

		self.size_x = size_x
		self.size_y = size_y

	def GenerateWorld(self):
		pass

	def AddPlayer(self, player):
		
		self.players[player.id] = player