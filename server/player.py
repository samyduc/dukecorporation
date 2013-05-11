import json
import gevent

class PlayerAction:
	IDLE = 1
	MOVING = 2
	WATCHING = 3
	PUSHING = 4

class Player:

	def __init__(self, redis_client, id, username, password):
		"""

		"""

		self.id = id
		self.username = username
		self.password = password
		self.auth = False

		self.action = PlayerAction.IDLE
		self.ChangeID(id)
		
		self.redis_client = redis_client

		self.linked_room = None

	def __repr__(self):
		return str(self.Serialize())

	def ChangeID(self, id):
		self.pub_key = "node:%s" % id

	def Serialize(self):

		return {'id': self.id,
				'username': self.username,
				'room':self.linked_room,
				'action': self.action}

	def Authentification(self):
		"""
		TODO: do a proper loggin

		"""

		self.auth = True
		return self.auth

	def Send_Data(self, data):

		data_raw = json.dumps(data)
		self.redis_client.publish(self.pub_key, data_raw)

	def Send_Connection(self):

		response = {'event': 'connection', 'status':self.auth}
		data_json = self.Serialize()
		response.update(data_json)
		
		#gevent.spawn(self.Send_Data, response)
		self.Send_Data(response)

	def Send_Update(self, data_json):
		response = {'event': 'update'}
		response.update(data_json)
		response.update(self.Serialize())

		#gevent.spawn(self.Send_Data, response)
		self.Send_Data(response)

	def Send_VoteDead(self, data_json):

		response = {'event': 'vote_dead'}
		response.update(data_json)
		response.update(self.Serialize())
