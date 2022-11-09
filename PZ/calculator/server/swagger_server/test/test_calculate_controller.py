# coding: utf-8

from __future__ import absolute_import

from flask import json
from six import BytesIO

from swagger_server.models.operation import Operation  # noqa: E501
from swagger_server.models.result import Result  # noqa: E501
from swagger_server.test import BaseTestCase


class TestCalculateController(BaseTestCase):
    """CalculateController integration test stubs"""

    def test_add_number(self):
        """Test case for add_number

        Addition of two numbers
        """
        body = Operation()
        response = self.client.open(
            '/calculate/sum',
            method='PUT',
            data=json.dumps(body),
            content_type='application/json')
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))

    def test_div_number(self):
        """Test case for div_number

        Division of two numbers
        """
        body = Operation()
        response = self.client.open(
            '/calculate/div',
            method='PUT',
            data=json.dumps(body),
            content_type='application/json')
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))

    def test_get_res(self):
        """Test case for get_res

        get result
        """
        response = self.client.open(
            '/calculate/get',
            method='GET')
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))

    def test_mul_number(self):
        """Test case for mul_number

        Multiplication of two numbers
        """
        body = Operation()
        response = self.client.open(
            '/calculate/mul',
            method='PUT',
            data=json.dumps(body),
            content_type='application/json')
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))

    def test_sub_number(self):
        """Test case for sub_number

        Subtraction of two numbers
        """
        body = Operation()
        response = self.client.open(
            '/calculate/sub',
            method='PUT',
            data=json.dumps(body),
            content_type='application/json')
        self.assert200(response,
                       'Response body is : ' + response.data.decode('utf-8'))


if __name__ == '__main__':
    import unittest
    unittest.main()
