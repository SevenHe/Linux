from django.http import HttpResponse, HttpResponseRedirect
from django.template import RequestContext
from django.shortcuts import render, render_to_response

# Create your views here.
def train_business(request):
    return render_to_response('train_business.html', context_instance=RequestContext(request))
