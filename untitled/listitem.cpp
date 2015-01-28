#include "listitem.h"
/*
ListItem::ListItem()
{
}

ITEM* ListItem::CreateItem(TYPEITEM type)
{
    ITEM* item=new ITEM;
    item->id=0;
    item->type=type;
    item->pillar=NULL;
    item->wall=NULL;
    if(type==ITEM_PILLAR)
    {
        item->pillar=new PILLAR;
        item->pillar->insert=new INSERTPILLAR[4];
        item->pillar->insert[0].side=FRONT;
        item->pillar->insert[1].side=BACK;
        item->pillar->insert[2].side=LEFT;
        item->pillar->insert[3].side=RIGHT;
        for(int i=0;i<4;i++)
        {
            item->pillar->insert[i].insertTop=0;
            item->pillar->insert[i].insertBottom=0;
        }
        item->pillar->height=0;
        item->pillar->top=false;
    }
    if(type==ITEM_WALL)
    {
        item->wall=new WALL;
        item->wall->wallTop=false;
        item->wall->height=0;
        item->wall->width=0;
    }
    return item;
}

void ListItem::AppendItem(int id, TYPEITEM type)
{
    ITEM* item=this->CreateItem(type);
    item->id=id;
    this->TableItem.append(item);
}

void ListItem::AppendItem(ITEM *item)
{
    this->TableItem.append(item);  
}

void ListItem::AppendChild(int idParent, CHILD *child)
{
    ITEM *item=this->getItem(idParent);
    item->child.append(child);
}

ITEM *ListItem::getItem(int id)
{
    foreach(ITEM* item,this->TableItem)
        if(item->id==id)
            return item;
    return NULL;
}

QList<ITEM*> ListItem::items()
{
    return this->TableItem;
}

void ListItem::RemoveItem(int id)
{
    foreach(ITEM *item,this->TableItem)
    {
        if(item->id==id)
        {
            if(item->type==ITEM_PILLAR)
            {
                delete[] item->pillar->insert;
                delete item->pillar;
            }
            if(item->type==ITEM_WALL)
            {
                foreach(CHILD *itemParent,item->child)
                {
                    this->RemoveItemChild(itemParent->idChild,item->id);
                    delete itemParent;
                }
                item->child.clear();
                delete item->wall;
            }
            if(!item->child.isEmpty())
            {
                foreach(CHILD *ItemChild,item->child)
                    delete ItemChild;
                item->child.clear();
            }
            this->TableItem.removeAt(this->TableItem.indexOf(item));
            delete item;
            return;
        }
    }
}


void ListItem::RemoveItemChild(int idParent, int idChild)
{
    ITEM *itemParent=this->getItem(idParent);
    if(itemParent!=NULL)
        foreach(CHILD *itemChild,itemParent->child)
        {
            if(idChild==itemChild->idChild)
            {
                itemParent->child.removeAt(itemParent->child.indexOf(itemChild));
                delete itemChild;
                return;
            }
        }
}


void ListItem::RemoveAll()
{
    foreach(ITEM* item,this->TableItem)
    {
        if(item->type==ITEM_PILLAR)
        {
            delete[] item->pillar->insert;
            delete item->pillar;
        }else delete item->wall;
        foreach(CHILD *ItemChild,item->child)
            delete ItemChild;
        item->child.clear();
        delete item;
    }
    this->TableItem.clear();
}


int ListItem::CountItem()
{
    return this->TableItem.count();
}

bool ListItem::isEmpty()
{
    return this->TableItem.isEmpty();
}*/
