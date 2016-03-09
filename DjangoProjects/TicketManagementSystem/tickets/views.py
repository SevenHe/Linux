# -*- coding: utf-8 -*-
from django.http import HttpResponse, HttpResponseRedirect, JsonResponse, Http404
from django.template import RequestContext
from django.core import serializers
from django.core.urlresolvers import reverse
from django.shortcuts import render, render_to_response
from django.contrib.auth.decorators import login_required  
from tickets.models import *
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
        return JsonResponse({'error': 'false', 'searching': 'false'})
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
def reservation(request):
    if re.findall('train|fly|bus', request.META['HTTP_REFERER'].encode('ascii')):
        m = re.match(r'(.+)(49\.140\.62\.120)(\/ticket\/)(.*)(\/.*\/)$', request.META['HTTP_REFERER'].encode('ascii'))
        serial = request.GET['serial']
        if m.group(4) == "train":
            try:
                ticket = TrainTicket.objects.get(serial=serial)
            except:
                return HttpResponse("发生未知错误！！！")
            else:
                return render_to_response('reservation.html', {'ticket': ticket, 't_type': 'train'}, context_instance=RequestContext(request))
        elif m.group(4) == "bus":
            try:
                ticket = BusTicket.objects.get(serial=serial)
            except:
                return HttpResponse("发生未知错误！！！")
            else:
                return render_to_response('reservation.html', {'ticket': ticket, 't_type': 'bus'}, context_instance=RequestContext(request))
        elif m.group(4) == "fly":
            try:
                ticket = FlyTicket.objects.get(serial=serial)
            except:
                return HttpResponse("发生未知错误！！！")
            else:
                return render_to_response('reservation.html', {'ticket': ticket, 't_type': 'fly'}, context_instance=RequestContext(request))
 
    else:
        return HttpResponse("非法访问！！！")
 
                        
@login_required(login_url='/account/turn_to_sign_in/')
def trade(request, t_type):
    """
    a more effective way is to add a count field, and
    i will put it into a list, iterate the list and
    save the ticket will be quick just like twenty lines' code.
    """
    if request.method != "POST":
        return HttpResponse("Illegal Access in trading!!")
    content = request.POST['content'].encode('ascii')
    (info, tickets) = content.split(',', 1)
    serial = info.split(' ')[0]
    number = int(info.split(' ')[1])
    ticket1, ticket2, ticket3 = [], [], []
    if number == 1:
        (ticket1, end) = tickets.split(',')
        ticket1 = ticket1.split(' ')
        ticket1[0] = int(ticket1[0])
    elif number == 2:
        (ticket1, ticket2, end) = tickets.split(',')
        ticket1 = ticket1.split(' ')
        ticket2 = ticket2.split(' ')
        for ticket in [ticket1, ticket2]:
            ticket[0] = int(ticket[0])
    elif number == 3:
        (ticket1, ticket2, ticket3, end) = tickets.split(',')
        ticket1 = ticket1.split(' ')
        ticket2 = ticket2.split(' ')
        ticket3 = ticket3.split(' ')
        for ticket in [ticket1, ticket2, ticket3]:
            ticket[0] = int(ticket[0])
    t1_number, t2_number, t3_number = 1, 0, 0
    if ticket1 and ticket2:
        if ticket1[1:] == ticket2[1:]:
            t1_number += 1 
            ticket2 = []
        else:
            t2_number = 1
            # just for easily understanding!
            ticket2[0] = t2_number
    if ticket1 and ticket3:
        if ticket1[1:] == ticket3[1:]:
            t1_number += 1
            ticket3 = []
        elif ticket2[1:] == ticket3[1:]:
            t2_number += 1
            ticket3 = []
        else:
            t3_number = 1
            ticket3[0] = t3_number
    ticket1[0] = t1_number
    if t_type == 'train':
        book_date = datetime.now()          
        try:
            train_ticket = TrainTicket.objects.get(serial=serial)
            for ticket in [ticket1, ticket2, ticket3]:
                if not ticket:
                    break
                try:
                    train_trade = TrainTrade.objects.get_or_create(user_id=request.user.id, 
                                            serial_id=train_ticket.id,
                                            book_date=book_date, genre=ticket[1], t_type=ticket[2],
                                            number=ticket[0])
                    if not train_trade[1]:
                        train_trade[0].number += ticket[0]
                        train_trade[0].save()
                except:
                    return HttpResponse("Trade Unknown Error!")
        except:
            return HttpResponse("Ticket Unkown Error!")
    elif t_type == 'fly': 
        book_date = datetime.now()          
        try:
            fly_ticket = FlyTicket.objects.get(serial=serial)
            for ticket in [ticket1, ticket2, ticket3]:
                if not ticket:
                    break
                try:
                    fly_trade = FlyTrade.objects.get_or_create(user_id=request.user.id, 
                                            serial_id=fly_ticket.id,
                                            book_date=book_date, genre=ticket[1], t_type=ticket[2],
                                            number=ticket[0])
                    if not fly_trade[1]:
                        fly_trade[0].number += ticket[0]
                        fly_trade[0].save()
                except:
                    return HttpResponse("Trade Unknown Error!")
        except:
            return HttpResponse("Ticket Unkown Error!")
    elif t_type == 'bus':
        book_date = datetime.now()          
        try:
            bus_ticket = BusTicket.objects.get(serial=serial)
            for ticket in [ticket1, ticket2, ticket3]:
                if not ticket:
                    break
                try:
                    bus_trade = BusTrade.objects.get_or_create(user_id=request.user.id, 
                                            serial_id=bus_ticket.id,
                                            book_date=book_date, genre=ticket[1], t_type=ticket[2],
                                            number=ticket[0])
                    if not bus_trade[1]:
                        bus_trade[0].number += ticket[0]
                        bus_trade[0].save()
                except:
                    return HttpResponse("Trade Unknown Error!")
        except:
            return HttpResponse("Ticket Unkown Error!") 
                                        
    return HttpResponseRedirect(reverse('personalize'))

@login_required(login_url='/account/turn_to_sign_in/')
def payment(request):
    """
    for now, just change the status and render the personal page!
    """
    if request.GET:
        ticket_type = request.GET['t_type'].encode('ascii')
        serial = request.GET['serial'].encode('ascii')
        genre_type = request.GET['genre_type']
        genre, t_type = genre_type.split(' ')
        user_id = request.user.id
        try:
            # may this place occur problems!
            if ticket_type == "train":
                if genre == '硬座'.decode('utf-8'):
                    genre = 'h'
                else:
                    genre = 's'
                if t_type == '成人票'.decode('utf-8'):
                    t_type = 'a'
                else:
                    t_type = 'c'
                ticket = TrainTicket.objects.get(serial=serial)
                trades = TrainTrade.objects.filter(user_id=user_id, serial_id=ticket.id, 
                                                genre=genre, t_type=t_type)
                for trade in trades:
                    trade.status = 2
                    trade.save()
                return HttpResponse("payed")
            elif ticket_type == "fly":
                if genre == '头等舱'.decode('utf-8'):
                    genre = 'f'
                else:
                    genre = 'e'
                if t_type == '全价票'.decode('utf-8'):
                    t_type = 'w'
                else:
                    t_type = 'p'
                ticket = FlyTicket.objects.get(serial=serial)
                trades = FlyTrade.objects.filter(user_id=user_id, serial_id=ticket.id,
                                                genre=genre, t_type=t_type)
                for trade in trades:
                    trade.status = 2
                    trade.save()
                return HttpResponse("payed")
            elif ticket_type == "bus":
                if genre == '硬座'.decode('utf-8'):
                    genre = 'h'
                else:
                    genre = 'u'
                if t_type == '成人票'.decode('utf-8'):
                    t_type = 'a'
                else:
                    t_type = 's'
                ticket = BusTicket.objects.get(serial=serial)
                trades = BusTrade.objects.filter(user_id=user_id, serial_id=ticket.id,
                                                genre=genre, t_type=t_type)
                for trade in trades:
                    trade.status = 2
                    trade.save()
                return HttpResponse("payed")
        except:
            return HttpResponse("Payment Unknown Error!!")
    else:
        return HttpResponse("Payment Illegal Access!!")

@login_required(login_url='/account/turn_to_sign_in/')
def cancel(request):
    """
    if the ticket has not been payed, so it will expired in 12 hours!
    and this place should use a form post method as the best!
    """
    if request.GET:
        ticket_type = request.GET['t_type'].encode('ascii')
        serial = request.GET['serial'].encode('ascii')
        genre_type = request.GET['genre_type']
        genre, t_type = genre_type.split(' ')
        user_id = request.user.id
        try:
            if ticket_type == "train":
                if genre == '硬座'.decode('utf-8'):
                    genre = 'h'
                else:
                    genre = 's'
                if t_type == '成人票'.decode('utf-8'):
                    t_type = 'a'
                else:
                    t_type = 'c'
                ticket = TrainTicket.objects.get(serial=serial)
                trades = TrainTrade.objects.filter(user_id=user_id, serial_id=ticket.id,
                                                    genre=genre, t_type=t_type)
                for trade in trades:
                    if trade.status == 1:
                        trade.delete()
                return HttpResponse("canceled")
            elif ticket_type == "fly":
                if genre == '头等舱'.decode('utf-8'):
                    genre = 'f'
                else:
                    genre = 'e'
                if t_type == '全价票'.decode('utf-8'):
                    t_type = 'w'
                else:
                    t_type = 'p'
                ticket = FlyTicket.objects.get(serial=serial)
                trades = FlyTrade.objects.filter(user_id=user_id, serial_id=ticket.id,
                                                genre=genre, t_type = t_type)
                for trade in trades:
                    if trade.status == 1:
                        trade.delete()
                return HttpResponse("canceled")
            elif ticket_type == "bus":
                if genre == '硬座'.decode('utf-8'):
                    genre = 'h'
                else:
                    genre = 'u'
                if t_type == '成人票'.decode('utf-8'):
                    t_type = 'a'
                else:
                    t_type = 's'
                ticket = BusTicket.objects.get(serial=serial)
                trades = BusTrade.objects.filter(user_id=user_id, serial_id=ticket.id,
                                                genre=genre, t_type=t_type)
                for trade in trades:
                    if trade.status == 1:
                        trade.delete()
                return HttpResponse("canceled")
        except:
            return HttpResponse("Cancellation Unknown Error!!")
    else:
        return HttpResponse("Cancellation Illegal Access!!")


