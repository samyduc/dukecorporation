import pika

channel = None

def on_open(connection):
    # Invoked when the connection is open
    connection.channel(on_channel_open)

def on_channel_open(new_channel):
    """Called when our channel has opened"""
    global channel
    channel = new_channel
    channel.queue_declare(queue="connection", durable=True, exclusive=False, auto_delete=True, callback=on_queue_declared)

def on_queue_declared(frame):
    """Called when RabbitMQ has told us our Queue has been declared, frame is the response from RabbitMQ"""
    channel.basic_consume(handle_delivery, queue='connection')

def handle_delivery(channel, method, header, body):
    """Called when we receive a message from RabbitMQ"""
    print body

    # resp back
    #channel.basic_publish(	'test_exchange',
    #                    	'test_routing_key',
    #                   	'message body value',
    #                    	pika.BasicProperties(	content_type='text/json',
    #                        						delivery_mode=1))

# Create our connection object, passing in the on_open method
parameters = pika.ConnectionParameters()
connection = pika.SelectConnection(parameters, on_open)

try:
    # Loop so we can communicate with RabbitMQ
    connection.ioloop.start()
except KeyboardInterrupt:
    # Gracefully close the connection
    connection.close()
    # Loop until we're fully closed, will stop on its own
    connection.ioloop.start()