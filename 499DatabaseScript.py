import json
from bson import json_util
from pymongo import MongoClient
from pprint import pprint

connection = MongoClient('localhost', 27017)
db = connection['stocks499']
collection = db['stocks']

def read_document():
	try:
		key = raw_input("Enter key: ")
    		value = raw_input("Enter value: ")

    		cursor = collection.find_one({ key : value })
		
		for document in cursor:
		pprint(document)

  	except ValidationError as ve:
    		abort(400, str(ve))
	
def main():
	read_document()

main()

input()
