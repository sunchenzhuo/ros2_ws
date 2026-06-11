from setuptools import find_packages
from setuptools import setup

setup(
    name='base_demo_cpp',
    version='0.0.0',
    packages=find_packages(
        include=('base_demo_cpp', 'base_demo_cpp.*')),
)
