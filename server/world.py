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

		for i in range(top_left_x, top_left_x + size_square):
			for j in range(top_left_y, top_left_y + size_square):
				if i >= 0 and j >= 0:
					around_rooms.append(self.board[i][j])

		return around_rooms

	def Shuffle(self):
		pass

	def AddPlayer(self, player):
		
		if player.username not in self.players:
			self.players[player.username] = player
		else: 
			player_store = self.players[player.username]
			player_store.id = player.id
			player = player_store

		if not player.linked_room:
			self.spawn_room.AddPlayer(player)


		return player

	def GetPlayerByID(self, id):
		current_player = None

		# search player
		for key, player in self.players.iteritems():
			if player.id == id:
				current_player = player
				break

		return current_player

	def UpdatePlayer(self, player, action, linked_room):
		"""
		Update a given player

		"""

		old_room = self.rooms[player.linked_room]
		old_room.RemovePlayer(player)

		new_room = self.rooms[linked_room]
		new_room.AddPlayer(player)

		player.action = action

		self.OnUpdatePlayer(player)

	def OnUpdatePlayer(self, player):
		"""
		Update all players concerned by a change

		"""

		# check if the player does not already exists

		# TODO
		# replace it

		current_room = self.rooms[player.linked_room]
		rooms = self.GetRoomFromCenter(current_room)
		
		data_json = {'rooms':[]}
		for room in rooms:
			data_json['rooms'].append(room.Serialize())

		for current_room in rooms:
			for key, player in current_room.players.iteritems():
				player.Send_Update(data_json)
