from rest_framework import serializers
from .models import State, Mode

class StateSerializer(serializers.ModelSerializer):
    class Meta:
        model = State
        fields = ['light_1']

class ModeSerializer(serializers.ModelSerializer):
    class Meta:
        model = Mode
        fields = ['mode']