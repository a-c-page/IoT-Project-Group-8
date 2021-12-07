from django.urls import path
from .views import state, home, mode
from django.contrib.staticfiles.urls import staticfiles_urlpatterns

urlpatterns = [
    path('', home),
    path('state/', state),
    path('mode/', mode)
]

urlpatterns += staticfiles_urlpatterns()