from django.contrib import admin
from TestModule.models import *
"""
search_fiels---to set the items to be searched.
list_display---to set which items to be showed in the model page.
"""
# Register your models here.
# between the two classes, must be indentation of one line.
class TagInline(admin.TabularInline):
    model = Tag
    
class ContactAdmin(admin.ModelAdmin):
    inlines = [TagInline]  # Inline
    fieldsets = (
        ['Main',{
            'fields':('name','email'),
        }],
        ['Advance',{
            'classes': ('collapse',),
            'fields': ('age',),
        }]

    )


admin.site.register(Contact, ContactAdmin)
admin.site.register([Test])