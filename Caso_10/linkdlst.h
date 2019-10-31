#ifndef LINKDLST_H
#define LINKDLST_H

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef struct list_head list_head;
typedef struct list_element list_element;

#define list_type(type) \
    type *

#define list(type, name) \
    list_type (type) name

#define list_push(list, value) do {                                           \
    typeof (*list) _v_copy = (typeof (*list)) value;                           \
    _list_push ((list_head **) &list, sizeof (_v_copy), &_v_copy);             \
    } while (0)                                                                   \

#define list_elem(list)                                                       \
    typeof (list)

#define list_elem_front(list)                                                 \
    ((typeof (list)) _list_front ((list_head *) list))                         \

#define list_elem_back(list)                                                  \
    ((typeof (list)) _list_back ((list_head *) list))                          \

#define list_elem_next(elem)                                                  \
    ((typeof (elem)) _list_next ((list_element *) elem))                       \

#define list_each(list, e)                                                    \
    for (typeof (*list) e, * _##e = list_elem_front (list),                    \
    * _##e##_next = list_elem_next (_##e); _##e;                          \
    _##e = _##e##_next, _##e##_next = list_elem_next (_##e))            \
    if (!memcpy (&e, _##e, sizeof (e))) {} else                      \

#ifndef _MSC_VER
#define list_find(list, value) ({                                          \
    list_elem (list) elem = list_elem_front (list);                         \
    for (; elem; elem = list_elem_next (elem))                              \
    if (*elem == value)                                                  \
    break;                                                            \
    elem;                                                                   \
    })
#else
template <class T> inline T * list_find (T * list, T value)
{
    list_elem (list) elem = list_elem_front (list);
    for (; elem; elem = list_elem_next (elem))
        if (*elem == value)
            return elem;
    return 0;
}
#endif

#define list_remove(list, value)                                              \
    list_elem_remove (list_find (list, value))                                 \

#define list_elem_remove(elem)                                                \
    _list_remove ((list_element *) elem)                                       \

#define list_length(list)                                                     \
    _list_length ((list_head *) (list))                                        \

#define list_back(list)                                                       \
    (*list_elem_back (list))                                                   \

#ifdef __cplusplus
extern "C"
{
#endif

struct list_head
{
    list_element * first, * last;
    size_t length;
};

struct list_element
{
    list_head * list;
    list_element * prev, * next;
};

static list_element * get_element (list_element * elem)
{
    return elem ? (elem - 1) : 0;
}

static void * get_value_ptr (list_element * elem)
{
    return elem ? (elem + 1) : 0;
}

size_t _list_length (list_head * list)
{
    return list ? list->length : 0;
}

void _list_push (list_head ** p_list, size_t value_size, void * value)
{
    if (!*p_list)
        *p_list = (list_head *) calloc (sizeof (list_head), 1);

    list_head * list = *p_list;

    ++ list->length;

    list_element * elem = (list_element *)
            malloc (sizeof (*elem) + value_size);

    memset (elem, 0, sizeof (*elem));
    memcpy (get_value_ptr (elem), value, value_size);

    elem->list = list;
    elem->prev = list->last;

    if (list->last)
    {
        list->last->next = elem;
        list->last = elem;
    }
    else
    {
        list->first = list->last = elem;
    }
}

list_element * _list_front (list_head * list)
{
    return list ? (list_element *) get_value_ptr (list->first) : 0;
}

list_element * _list_back (list_head * list)
{
    return list ? (list_element *) get_value_ptr (list->last) : 0;
}

list_element * _list_next (list_element * elem)
{
    if (!elem || ! (elem = get_element (elem)->next))
        return 0;

    return (list_element *) get_value_ptr (elem);
}

void _list_remove (list_element * elem)
{
    if (!elem)
        return;

    elem = get_element (elem);

    list_head * list = elem->list;

    -- list->length;

    if (elem->next)
        elem->next->prev = elem->prev;

    if (elem->prev)
        elem->prev->next = elem->next;

    if (elem == list->first)
        list->first = elem->next;

    if (elem == list->last)
        list->last = elem->prev;

    free (elem);
}

#ifdef __cplusplus
}
#endif

#endif
