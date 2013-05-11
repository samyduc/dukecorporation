
import time

class RoomType:

	poison = 1 # le second qui rentre tue le premier
	flood = 2 # 5s pour sortir de la salle
	dead = 3 # rentre signifie la mort
	deadporcent = 4 # pourcentage de chance de mourir
	safe = 5 # totalemetn sans danger
	teleport = 6 # teleporte vers une autre salle du meme type
	prison = 7 # bloque pendant un certain cooldown
	spawn = 8 # spawn de depart
	exit = 9 # salle de sortie



class Room:

	def __init__(self, id, type_room, x, y):
		"""
		Generic Room

		"""

		self.players = {}
		self.dead_nb = 0

		self.vote_dead_start = 0
		self.vote_dead = {}
		# percentage
		self.vote_dead_needed = 0.5

		self.id = id
		self.type = type_room

		self.x = x
		self.y = y

	def __repr__(self):
		return str(self.Serialize())

	def RemovePlayer(self, player):
		if player.username in self.players:
			print("Del player %s in room %s" % (player, self))
			del self.players[player.username]
			player.linked_room = None
		else:
			print("WARNING: player:%s not in a room %s" % (player, self))

	def AddPlayer(self, player):

		if player.linked_room:
			print("WARNING: player:%s is already in a room %s" % (player, self))

		print("Add player %s in room %s" % (player, self))
		self.players[player.username] = player
		player.linked_room = self.id

	def VoteDead(self, player_vote, player_dead):

		if player.username not in self.player:
			print("WARNING: player:%s not in a room %s" % (player, self))

		if len(self.vote_dead) == 0:
			self.vote_dead_start = time.time()

		list_vote = self.vote_dead[player_dead.username]

		# cannot vote twice honey
		if player_vote.username not in list_vote:
			list_vote.append(player_vote.username)

	def CheckVoteDead(self):

		players_killed = []

		for player_dead_username, player_vote_list in self.vote_dead.iteritems():

			if len(player_vote_list) / len(self.players) > self.vote_dead_needed:
				# killed
				players_killed.append(self.players[player_dead_username])
				self.dead_nb += 1
			else:
				print("WARNING: vote dead rejected :%s in a room %s" % (player_dead_username, self))

		self.vote_dead.clear()

		return players_killed

	def Serialize(self):
		return {'id':self.id, 
				'players':[player.Serialize() for key, player in self.players.iteritems()],
				'dead_nb':self.dead_nb,
				'type':self.type,
				'x': self.x,
				'y': self.y}