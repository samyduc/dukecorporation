from gevent import monkey
monkey.patch_all()

import gevent


import json
import redis

from world import World
from player import Player



class Server:


	def __init__(self):
		self.globalWorld = World(50 , 50)
		self.globalWorld.GenerateWorld()

		self.redis_subscriber = redis.Redis("localhost")
		self.ps = self.redis_subscriber.pubsub()
		self.ps.subscribe("world:1")

		self.client = redis.Redis("localhost")

	def BuildPlayer(self, id, username, password):

		return Player(self.client, id, username, password)

	def OnAuthentification(self, json_data):
		player = self.BuildPlayer(json_data['id'], json_data['username'], json_data['password'])
		if player.Authentification():
			player = self.globalWorld.AddPlayer(player)

		player.Send_Connection()
		self.globalWorld.OnUpdatePlayer(player)

	def OnUpdate(self, json_data):
		player = self.globalWorld.GetPlayerByID(json_data['id'])

		if player:
			self.globalWorld.UpdatePlayer(player, json_data['action'], json_data['room'])

	def MainLoop(self):
		green_logic = gevent.spawn(self.MainLoopLogic)
		green_redis = gevent.spawn(self.MainLoopRedis)

		gevent.joinall((green_logic, green_redis))

	def MainLoopLogic(self):

		while True:
			print 'MainLoopLogic'
			gevent.sleep()

	def MainLoopRedis(self):
		gevent.sleep()

		for item in self.ps.listen():
			if item['type'] == 'message':
				print item['channel']
				print item['data']
				json_data = json.loads(item['data'])

				# filter events
				if 'event' in json_data:

					event = json_data['event']

					if event == 'connection':
						gevent.spawn(self.OnAuthentification, json_data)
					elif event == 'update':
						gevent.spawn(self.OnUpdate, json_data)
					else:
						print("unknown event")

			gevent.sleep()

				#client.publish('node:%s' % json_data['id'], item['data'])

if __name__ == "__main__":
	server = Server()
	server.MainLoop()