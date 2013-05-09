import json

class Player:

	def __init__(self, redis_client, id, username, password):
		"""

		"""

		self.id = id
		self.username = username
		self.password = password
		self.auth = False

		self.pub_key = "node:%s" % id
		self.redis_client = redis_client

		self.linked_room = None

	def Serialize(self):

		id_room = -1

		if self.linked_room:
			id_room = self.linked_room.id

		return {'id': self.id,
				'username': self.username,
				'room':id_room}

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
		
		self.Send_Data(response)

	def Send_Update(self, data_json):
		response = {'event': 'update'}
		response.update(data_json)

		self.Send_Data(response)


