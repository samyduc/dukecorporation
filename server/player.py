import json

class Player:

	def __init__(redis_client, id, username, password):
		"""

		"""

		self.id = id
		self.username = username
		self.password = password
		self.auth = False

		self.pub_key = "node:%s" % id
		self.redis_client = redis_client

		self.x = 0
		self.y = 0

	def Authentification(self):
		"""
		TODO: do a proper loggin

		"""

		self.auth = True
		return self.auth

	def Send_Connection(self):

		response = {'event': connection, 'status':self.auth}
		response_json = json.dumps(response)

		self.redis_client.publish(self.pub_key, response_json)