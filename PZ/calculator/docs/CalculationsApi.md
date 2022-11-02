# Calculator.CalculationsApi

All URIs are relative to *http://localhost*

Method | HTTP request | Description
------------- | ------------- | -------------
[**calculatesumPut**](CalculationsApi.md#calculatesumPut) | **PUT** /calculatesum | Addition of two numbers



## calculatesumPut

> calculatesumPut()

Addition of two numbers

### Example

```javascript
import Calculator from 'calculator';

let apiInstance = new Calculator.CalculationsApi();
apiInstance.calculatesumPut((error, data, response) => {
  if (error) {
    console.error(error);
  } else {
    console.log('API called successfully.');
  }
});
```

### Parameters

This endpoint does not need any parameter.

### Return type

null (empty response body)

### Authorization

No authorization required

### HTTP request headers

- **Content-Type**: Not defined
- **Accept**: Not defined

