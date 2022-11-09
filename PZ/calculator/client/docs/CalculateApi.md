# swagger_client.CalculateApi

All URIs are relative to *https://localhost:8080*

Method | HTTP request | Description
------------- | ------------- | -------------
[**add_number**](CalculateApi.md#add_number) | **PUT** /calculate/sum | Addition of two numbers
[**div_number**](CalculateApi.md#div_number) | **PUT** /calculate/div | Division of two numbers
[**get_res**](CalculateApi.md#get_res) | **GET** /calculate/get | get result
[**mul_number**](CalculateApi.md#mul_number) | **PUT** /calculate/mul | Multiplication of two numbers
[**sub_number**](CalculateApi.md#sub_number) | **PUT** /calculate/sub | Subtraction of two numbers

# **add_number**
> Operation add_number(body)

Addition of two numbers

### Example
```python
from __future__ import print_function
import time
import swagger_client
from swagger_client.rest import ApiException
from pprint import pprint

# create an instance of the API class
api_instance = swagger_client.CalculateApi()
body = swagger_client.Operation() # Operation | 

try:
    # Addition of two numbers
    api_response = api_instance.add_number(body)
    pprint(api_response)
except ApiException as e:
    print("Exception when calling CalculateApi->add_number: %s\n" % e)
```

### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **body** | [**Operation**](Operation.md)|  | 

### Return type

[**Operation**](Operation.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: application/json
 - **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **div_number**
> Operation div_number(body)

Division of two numbers

### Example
```python
from __future__ import print_function
import time
import swagger_client
from swagger_client.rest import ApiException
from pprint import pprint

# create an instance of the API class
api_instance = swagger_client.CalculateApi()
body = swagger_client.Operation() # Operation | 

try:
    # Division of two numbers
    api_response = api_instance.div_number(body)
    pprint(api_response)
except ApiException as e:
    print("Exception when calling CalculateApi->div_number: %s\n" % e)
```

### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **body** | [**Operation**](Operation.md)|  | 

### Return type

[**Operation**](Operation.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: application/json
 - **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **get_res**
> Result get_res()

get result

### Example
```python
from __future__ import print_function
import time
import swagger_client
from swagger_client.rest import ApiException
from pprint import pprint

# create an instance of the API class
api_instance = swagger_client.CalculateApi()

try:
    # get result
    api_response = api_instance.get_res()
    pprint(api_response)
except ApiException as e:
    print("Exception when calling CalculateApi->get_res: %s\n" % e)
```

### Parameters
This endpoint does not need any parameter.

### Return type

[**Result**](Result.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: Not defined
 - **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **mul_number**
> Operation mul_number(body)

Multiplication of two numbers

### Example
```python
from __future__ import print_function
import time
import swagger_client
from swagger_client.rest import ApiException
from pprint import pprint

# create an instance of the API class
api_instance = swagger_client.CalculateApi()
body = swagger_client.Operation() # Operation | 

try:
    # Multiplication of two numbers
    api_response = api_instance.mul_number(body)
    pprint(api_response)
except ApiException as e:
    print("Exception when calling CalculateApi->mul_number: %s\n" % e)
```

### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **body** | [**Operation**](Operation.md)|  | 

### Return type

[**Operation**](Operation.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: application/json
 - **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

# **sub_number**
> Operation sub_number(body)

Subtraction of two numbers

### Example
```python
from __future__ import print_function
import time
import swagger_client
from swagger_client.rest import ApiException
from pprint import pprint

# create an instance of the API class
api_instance = swagger_client.CalculateApi()
body = swagger_client.Operation() # Operation | 

try:
    # Subtraction of two numbers
    api_response = api_instance.sub_number(body)
    pprint(api_response)
except ApiException as e:
    print("Exception when calling CalculateApi->sub_number: %s\n" % e)
```

### Parameters

Name | Type | Description  | Notes
------------- | ------------- | ------------- | -------------
 **body** | [**Operation**](Operation.md)|  | 

### Return type

[**Operation**](Operation.md)

### Authorization

No authorization required

### HTTP request headers

 - **Content-Type**: application/json
 - **Accept**: application/json

[[Back to top]](#) [[Back to API list]](../README.md#documentation-for-api-endpoints) [[Back to Model list]](../README.md#documentation-for-models) [[Back to README]](../README.md)

