import json

from rest_framework.parsers import JSONParser
from .models import State, Mode
from .serializers import StateSerializer, ModeSerializer
from django.http import JsonResponse
from django.views.decorators.csrf import csrf_exempt
from django.shortcuts import render, redirect
import requests

@csrf_exempt
def state(request):
    if request.method == 'GET':
        state = State.objects.all()
        serializer = StateSerializer(state, many=True)
        return JsonResponse(serializer.data[-1], safe=False)
    elif request.method == 'POST':
        unicode = request.body.decode('utf-8')
        data = {"light_1": unicode[6:]}
        serializer = StateSerializer(data=data)

        if serializer.is_valid():
            serializer.save()
            return redirect("/")
        return JsonResponse(serializer.errors, status=400)

@csrf_exempt
def mode(request):
    if request.method == 'GET':
        state = Mode.objects.all()
        serializer = ModeSerializer(state, many=True)
        return JsonResponse(serializer.data[-1], safe=False)
    elif request.method == 'POST':
        unicode = request.body.decode('utf-8')
        data = {"mode": unicode[5:]}
        serializer = ModeSerializer(data=data)

        if serializer.is_valid():
            serializer.save()
            return redirect("/")
        return JsonResponse(serializer.errors, status=400)


def home(request):
    x = requests.get('https://iotprojecttam.herokuapp.com/state/')
    data = x.json()
    y = requests.get('https://iotprojecttam.herokuapp.com/mode/')
    tempData = y.json()
    currentState = data['light_1'] # Get the latest data
    currentMode = tempData['mode'] # Get the latest mode
    return render(request, "app.html", {'currentState': currentState, 'currentMode': currentMode})
