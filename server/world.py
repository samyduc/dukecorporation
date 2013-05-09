import player
import room

class World:


	def __init__(self, size_x, size_y):
		self.players = {}
		self.rooms = {}
		self.board = []

		self.size_x = size_x
		self.size_y = size_y

		self.id_generator = 0

		self.spawn_room = None
		self.exit_room = None

	def GenerateWorld(self):
		
		self.rooms.clear()

		for i in range(self.size_x):
			line = []
			for j in range(self.size_y):
				new_room = room.Room(self.id_generator, room.RoomType.safe, i, j)
				self.rooms[self.id_generator] = new_room
				line.append(new_room)

				self.id_generator += 1

			self.board.append(line)

		# put a spawner
		self.spawn_room = self.rooms[self.size_x/2 + self.size_y/2]
		self.spawn_room.type = room.RoomType.spawn

		# put an exit
		self.exit_room = self.rooms[0]
		self.exit_room.type = room.RoomType.exit

	def GetRoomFromCenter(self, center_room):

		distance_from_center = 1

		size_square = 1 + 2**distance_from_center

		top_left_x = center_room.x - size_square / 2
		top_left_y = center_room.y - size_square / 2

		around_rooms = []

		for i in range(top_left_x, top_left_x + size_square - 1):
			for j in range(top_left_y, top_left_y + size_square - 1):
				if i > 0 and j > 0:
					around_rooms.append(self.board[i][j])

		return around_rooms

	def Shuffle(self):
		pass

	def AddPlayer(self, player):
		
		self.players[player.username] = player

		if not player.linked_room:
			player.linked_room = self.spawn_room

	def UpdatePlayer(self, player):
		"""
		Update a given player

		"""

		current_room = player.linked_room
		rooms = self.GetRoomFromCenter(current_room)

		data_json = [room.Serialize() for room in rooms]

		return data_json