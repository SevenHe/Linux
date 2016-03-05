# -*- coding: utf-8 -*-
from django.http import HttpResponse, HttpResponseRedirect, JsonResponse, Http404
from django.template import RequestContext
from django.core import serializers
from django.shortcuts import render, render_to_response
from django.contrib.auth.decorators import login_required  
from tickets.models import TrainTicket
from datetime import datetime

# sometimes, JsonResponse is not so useful!It does more thing than HttpResponse for you!!!
# Create your views here.
@login_required(login_url='/account/turn_to_sign_in/')
def train_business(request):
    return render_to_response('train_business.html', context_instance=RequestContext(request))

def ajax_get_train(request):
    # sometimes, it did wrong work!
    if not request.is_ajax():
        raise Http404
    get_start = request.GET['start']
    get_terminus = request.GET['terminus']
    get_date = request.GET['date']
    try:
        get_date_object = datetime.strptime(get_date, '%Y-%m-%d')
    except:
        return JsonResponse({'error': 'true', 'searching': 'false'})
    if get_start and get_terminus and get_date:
        try:
            tickets = TrainTicket.objects.filter(start=get_start, terminus=get_terminus,
                                                departure__year=get_date_object.year,
                                                departure__month=get_date_object.month,
                                                departure__day=get_date_object.day)
        except:
            return JsonResponse({'error': 'true', 'searching': 'false'})
        else:
            # just for query set!
            if tickets:
                items = serializers.serialize("json", tickets)
                return HttpResponse(items)
            else:
                return JsonResponse({'searching': 'true', 'error': 'false'})
    else:
        return JsonResponse({'error': 'true', 'searching': 'false'})
                        
@login_required(login_url='/account/turn_to_sign_in/')
def fly_business(request):
    return render_to_response('fly_business.html', context_instance=RequestContext(request))

def ajax_get_fly(request):
    # sometimes, it did wrong work!
    if not request.is_ajax():
        raise Http404
    get_start = request.GET['start']
    get_terminus = request.GET['terminus']
    get_date = request.GET['date']
    try:
        get_date_object = datetime.strptime(get_date, '%Y-%m-%d')
    except:
        return JsonResponse({'error': 'true', 'searching': 'false'})
    if get_start and get_terminus and get_date:
        try:
            tickets = FlyTicket.objects.filter(start=get_start, terminus=get_terminus,
                                                departure__year=get_date_object.year,
                                                departure__month=get_date_object.month,
                                                departure__day=get_date_object.day)
        except:
            return JsonResponse({'error': 'true', 'searching': 'false'})
        else:
            # just for query set!
            if tickets:
                items = serializers.serialize("json", tickets)
                return HttpResponse(items)
            else:
                return JsonResponse({'searching': 'true', 'error': 'false'})
    else:
        return JsonResponse({'error': 'true', 'searching': 'false'})
                        
@login_required(login_url='/account/turn_to_sign_in/')
def bus_business(request):
    return render_to_response('bus_business.html', context_instance=RequestContext(request))

def ajax_get_bus(request):
    # sometimes, it did wrong work!
    if not request.is_ajax():
        raise Http404
    get_start = request.GET['start']
    get_terminus = request.GET['terminus']
    get_date = request.GET['date']
    try:
        get_date_object = datetime.strptime(get_date, '%Y-%m-%d')
    except:
        return JsonResponse({'error': 'true', 'searching': 'false'})
    if get_start and get_terminus and get_date:
        try:
            tickets = BusTicket.objects.filter(start=get_start, terminus=get_terminus,
                                                departure__year=get_date_object.year,
                                                departure__month=get_date_object.month,
                                                departure__day=get_date_object.day)
        except:
            return JsonResponse({'error': 'true', 'searching': 'false'})
        else:
            # just for query set!
            if tickets:
                items = serializers.serialize("json", tickets)
                return HttpResponse(items)
            else:
                return JsonResponse({'searching': 'true', 'error': 'false'})
    else:
        return JsonResponse({'error': 'true', 'searching': 'false'})

import re
@login_required(login_url='/account/turn_to_sign_in/')
def payment(request):
    if re.findall('train|fly|bus', request.META['HTTP_REFERER'].encode('ascii')):
        m = re.match(r'(.+)(49\.140\.62\.120)(\/ticket\/)(.*)(\/.*\/)$', request.META['HTTP_REFERER'].encode('ascii'))
        serial = request.GET['serial']
        if m.group(4) == "train":
            try:
                ticket = TrainTicket.objects.get(serial=serial)
            except:
                return HttpResponse("发生未知错误！！！")
            else:
                return render_to_response('payment.html', {'ticket': ticket, 't_type': 'train'}, context_instance=RequestContext(request))
        elif m.group(4) == "bus":
            try:
                ticket = BusTicket.objects.get(serial=serial)
            except:
                return HttpResponse("发生未知错误！！！")
            else:
                return render_to_response('payment.html', {'ticket': ticket, 't_type': 'bus'}, context_instance=RequestContext(request))
        elif m.group(4) == "fly":
            try:
                ticket = FlyTicket.objects.get(serial=serial)
            except:
                return HttpResponse("发生未知错误！！！")
            else:
                return render_to_response('payment.html', {'ticket': ticket, 't_type': 'fly'}, context_instance=RequestContext(request))
 
    else:
        return HttpResponse("非法访问！！！")
 
                        

