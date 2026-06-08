# generated from rosidl_generator_py/resource/_idl.py.em
# with input from base_demo_cpp:msg/BaseStatus.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_BaseStatus(type):
    """Metaclass of message 'BaseStatus'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('base_demo_cpp')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'base_demo_cpp.msg.BaseStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__base_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__base_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__base_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__base_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__base_status

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class BaseStatus(metaclass=Metaclass_BaseStatus):
    """Message class 'BaseStatus'."""

    __slots__ = [
        '_seq',
        '_vx',
        '_vy',
        '_wz',
        '_battery_voltage',
        '_err',
        '_cmd_timeout',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'seq': 'int32',
        'vx': 'double',
        'vy': 'double',
        'wz': 'double',
        'battery_voltage': 'double',
        'err': 'string',
        'cmd_timeout': 'boolean',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.seq = kwargs.get('seq', int())
        self.vx = kwargs.get('vx', float())
        self.vy = kwargs.get('vy', float())
        self.wz = kwargs.get('wz', float())
        self.battery_voltage = kwargs.get('battery_voltage', float())
        self.err = kwargs.get('err', str())
        self.cmd_timeout = kwargs.get('cmd_timeout', bool())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.seq != other.seq:
            return False
        if self.vx != other.vx:
            return False
        if self.vy != other.vy:
            return False
        if self.wz != other.wz:
            return False
        if self.battery_voltage != other.battery_voltage:
            return False
        if self.err != other.err:
            return False
        if self.cmd_timeout != other.cmd_timeout:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def seq(self):
        """Message field 'seq'."""
        return self._seq

    @seq.setter
    def seq(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'seq' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'seq' field must be an integer in [-2147483648, 2147483647]"
        self._seq = value

    @builtins.property
    def vx(self):
        """Message field 'vx'."""
        return self._vx

    @vx.setter
    def vx(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'vx' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'vx' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._vx = value

    @builtins.property
    def vy(self):
        """Message field 'vy'."""
        return self._vy

    @vy.setter
    def vy(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'vy' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'vy' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._vy = value

    @builtins.property
    def wz(self):
        """Message field 'wz'."""
        return self._wz

    @wz.setter
    def wz(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'wz' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'wz' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._wz = value

    @builtins.property
    def battery_voltage(self):
        """Message field 'battery_voltage'."""
        return self._battery_voltage

    @battery_voltage.setter
    def battery_voltage(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'battery_voltage' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'battery_voltage' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._battery_voltage = value

    @builtins.property
    def err(self):
        """Message field 'err'."""
        return self._err

    @err.setter
    def err(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'err' field must be of type 'str'"
        self._err = value

    @builtins.property
    def cmd_timeout(self):
        """Message field 'cmd_timeout'."""
        return self._cmd_timeout

    @cmd_timeout.setter
    def cmd_timeout(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'cmd_timeout' field must be of type 'bool'"
        self._cmd_timeout = value
