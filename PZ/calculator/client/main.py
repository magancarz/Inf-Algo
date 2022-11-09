from __future__ import print_function
import time
import swagger_client
from swagger_client.rest import ApiException
from pprint import pprint
import urllib3
urllib3.disable_warnings()

config = swagger_client.Configuration()
config.host = "http://127.0.0.1:8080"
config.verify_ssl = False

# create an instance of the API class
client = swagger_client.ApiClient(configuration=config)

try:
    # Addition of two numbers
    print("Test of adding two numbers: 10 + 5")
    api_instance = swagger_client.CalculateApi(api_client=client)
    body = swagger_client.Operation(10, 5)
    api_response = api_instance.add_number(body)
    pprint(api_response.num1)
except ApiException as e:
    print("Exception when calling CalculateApi->add_number: %s\n" % e)

try:
    # Addition of two numbers
    print("Test of subtracting two numbers: 10 - 5")
    api_instance = swagger_client.CalculateApi(api_client=client)
    body = swagger_client.Operation(10, 5)
    api_response = api_instance.sub_number(body)
    pprint(api_response.num1)
except ApiException as e:
    print("Exception when calling CalculateApi->add_number: %s\n" % e)

try:
    # Addition of two numbers
    print("Test of dividing two numbers: 10 / 5")
    api_instance = swagger_client.CalculateApi(api_client=client)
    body = swagger_client.Operation(10, 5)
    api_response = api_instance.div_number(body)
    pprint(api_response.num1)
except ApiException as e:
    print("Exception when calling CalculateApi->add_number: %s\n" % e)

try:
    # Addition of two numbers
    print("Test of subtracting two numbers: 10 * 5")
    api_instance = swagger_client.CalculateApi(api_client=client)
    body = swagger_client.Operation(10, 5)
    api_response = api_instance.mul_number(body)
    pprint(api_response.num1)
except ApiException as e:
    print("Exception when calling CalculateApi->add_number: %s\n" % e)