# coding: utf-8

"""
    Calculator

    No description provided (generated by Swagger Codegen https://github.com/swagger-api/swagger-codegen)  # noqa: E501

    OpenAPI spec version: 1.0
    
    Generated by: https://github.com/swagger-api/swagger-codegen.git
"""

import pprint
import re  # noqa: F401

import six

class Operation(object):
    """NOTE: This class is auto generated by the swagger code generator program.

    Do not edit the class manually.
    """
    """
    Attributes:
      swagger_types (dict): The key is attribute name
                            and the value is attribute type.
      attribute_map (dict): The key is attribute name
                            and the value is json key in definition.
    """
    swagger_types = {
        'num1': 'int',
        'num2': 'int'
    }

    attribute_map = {
        'num1': 'num1',
        'num2': 'num2'
    }

    def __init__(self, num1=None, num2=None):  # noqa: E501
        """Operation - a model defined in Swagger"""  # noqa: E501
        self._num1 = None
        self._num2 = None
        self.discriminator = None
        self.num1 = num1
        self.num2 = num2

    @property
    def num1(self):
        """Gets the num1 of this Operation.  # noqa: E501


        :return: The num1 of this Operation.  # noqa: E501
        :rtype: int
        """
        return self._num1

    @num1.setter
    def num1(self, num1):
        """Sets the num1 of this Operation.


        :param num1: The num1 of this Operation.  # noqa: E501
        :type: int
        """
        if num1 is None:
            raise ValueError("Invalid value for `num1`, must not be `None`")  # noqa: E501

        self._num1 = num1

    @property
    def num2(self):
        """Gets the num2 of this Operation.  # noqa: E501


        :return: The num2 of this Operation.  # noqa: E501
        :rtype: int
        """
        return self._num2

    @num2.setter
    def num2(self, num2):
        """Sets the num2 of this Operation.


        :param num2: The num2 of this Operation.  # noqa: E501
        :type: int
        """
        # if num2 is None:
        #     raise ValueError("Invalid value for `num2`, must not be `None`")  # noqa: E501

        self._num2 = num2

    def to_dict(self):
        """Returns the model properties as a dict"""
        result = {}

        for attr, _ in six.iteritems(self.swagger_types):
            value = getattr(self, attr)
            if isinstance(value, list):
                result[attr] = list(map(
                    lambda x: x.to_dict() if hasattr(x, "to_dict") else x,
                    value
                ))
            elif hasattr(value, "to_dict"):
                result[attr] = value.to_dict()
            elif isinstance(value, dict):
                result[attr] = dict(map(
                    lambda item: (item[0], item[1].to_dict())
                    if hasattr(item[1], "to_dict") else item,
                    value.items()
                ))
            else:
                result[attr] = value
        if issubclass(Operation, dict):
            for key, value in self.items():
                result[key] = value

        return result

    def to_str(self):
        """Returns the string representation of the model"""
        return pprint.pformat(self.to_dict())

    def __repr__(self):
        """For `print` and `pprint`"""
        return self.to_str()

    def __eq__(self, other):
        """Returns true if both objects are equal"""
        if not isinstance(other, Operation):
            return False

        return self.__dict__ == other.__dict__

    def __ne__(self, other):
        """Returns true if both objects are not equal"""
        return not self == other