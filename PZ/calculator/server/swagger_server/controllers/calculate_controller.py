import connexion
import six

from swagger_server.models.operation import Operation  # noqa: E501
from swagger_server.models.result import Result  # noqa: E501
from swagger_server import util


def add_number(body):  # noqa: E501
    """Addition of two numbers

     # noqa: E501

    :param body: 
    :type body: dict | bytes

    :rtype: Operation
    """
    if connexion.request.is_json:
        body = Operation.from_dict(connexion.request.get_json())  # noqa: E501
    return body.num1 + body.num2


def div_number(body):  # noqa: E501
    """Division of two numbers

     # noqa: E501

    :param body: 
    :type body: dict | bytes

    :rtype: Operation
    """
    if connexion.request.is_json:
        body = Operation.from_dict(connexion.request.get_json())  # noqa: E501
    return body.num1 / body.num2


def get_res():  # noqa: E501
    """get result

     # noqa: E501


    :rtype: Result
    """
    return 'do some magic!'


def mul_number(body):  # noqa: E501
    """Multiplication of two numbers

     # noqa: E501

    :param body: 
    :type body: dict | bytes

    :rtype: Operation
    """
    if connexion.request.is_json:
        body = Operation.from_dict(connexion.request.get_json())  # noqa: E501
    return body.num1 * body.num2


def sub_number(body):  # noqa: E501
    """Subtraction of two numbers

     # noqa: E501

    :param body: 
    :type body: dict | bytes

    :rtype: Operation
    """
    if connexion.request.is_json:
        body = Operation.from_dict(connexion.request.get_json())  # noqa: E501
    return body.num1 - body.num2
