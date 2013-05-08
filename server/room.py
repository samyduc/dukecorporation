

class RoomType:

	poison = 1 # le second qui rentre tue le premier
	flood = 2 # 5s pour sortir de la salle
	dead = 3 # rentre signifie la mort
	deadporcent = 4 # pourcentage de chance de mourir
	safe = 5 # totalemetn sans danger
	teleport = 6 # teleporte vers une autre salle du même type
	prison = 7 # bloque pendant un certain cooldown
	spawn = 8 # spawn de depart
	exit = 9 # salle de sortie



class Room:

	def __init__(self, id, type_room, x, y):
		"""
		Generic Room

		"""

		self.players = []
		self.dead_nb = 0

		self.id = id
		self.type = type_room

		self.x = x
		self.y = y

	def Serialize(self):
		return {'id':self.id, 
				'players':[player.Serialize() for player in players],
				'dead_nb':self.dead_nb,
				'type':self.type,
				'x': self.x,
				'y': self.y}