#include <stdio.h>
#include <stdlib.h>

struct person
{
    char name;
    struct person* next;
};

struct kassaeins
{
    struct person* person;
    struct kassaeins* next;
};

struct kassazwei
{
    struct person* person;
    struct kassazwei* next;
};

struct person* createPerson(char name)
{
    struct person* newPerson = (struct person*)malloc(sizeof(struct person));
    newPerson->name = name;

    return newPerson;
};

struct kassaeins* createKassaeins(struct person* person)
{
    struct kassaeins* newKassa = (struct kassaeins*)malloc(sizeof(struct kassaeins));
    newKassa->person = person;

    return newKassa;
};

struct kassazwei* createKassazwei(struct person* person)
{
    struct kassazwei* newKassa = (struct kassazwei*)malloc(sizeof(struct kassazwei));
    newKassa->person = person;

    return newKassa;
};

struct person* addLastQueue(struct person* head, struct person* newPerson)
{
    if(head == NULL)
    {
        newPerson->next = NULL;
        return newPerson;
    }
    else
    {
        struct person* temp = head;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newPerson;
        newPerson->next = NULL;
        return head;
    }
};

struct kassaeins* addLastKassaeins(struct kassaeins* head, struct kassaeins* newPerson)
{
    if(head == NULL)
    {
        newPerson->next = NULL;
        return newPerson;
    }
    else
    {
        struct kassaeins* temp = head;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newPerson;
        newPerson->next = NULL;
        return head;
    }
};

struct kassazwei* addLastKassazwei(struct kassazwei* head, struct kassazwei* newPerson)
{
    if(head == NULL)
    {
        newPerson->next = NULL;
        return newPerson;
    }
    else
    {
        struct kassazwei* temp = head;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newPerson;
        newPerson->next = NULL;
        return head;
    }
};

int getCountQueue(struct person* head)
{
    int count = 0;
    struct person* temp = head;

    while(temp != NULL)
    {
        temp = temp->next;
        count++;
    }

    return count;
}

int getCountKassaeins(struct kassaeins* head)
{
    int count = 0;
    struct kassaeins* temp = head;

    while(temp != NULL)
    {
        temp = temp->next;
        count++;
    }

    return count;
}

int getCountKassazwei(struct kassazwei* head)
{
    int count = 0;
    struct kassazwei* temp = head;

    while(temp != NULL)
    {
        temp = temp->next;
        count++;
    }

    return count;
}

void printQueue(struct person* head)
{
    printf("Personen: %d\n", getCountQueue(head));
    struct person* temp = head;

    while(temp != NULL)
    {
        printf("%c ", temp->name);
        temp = temp->next;
    }
    printf("\n");
}

void printKassaeins(struct kassaeins* head)
{
    printf("Kassa 1: %d\n", getCountKassaeins(head));
    struct kassaeins* temp = head;

    while(temp != NULL)
    {
        printf("%c ", temp->person->name);
        temp = temp->next;
    }
    printf("\n");
}

void printKassazwei(struct kassazwei* head)
{
    printf("Kassa 2: %d\n", getCountKassazwei(head));
    struct kassazwei* temp = head;

    while(temp != NULL)
    {
        printf("%c ", temp->person->name);
        temp = temp->next;
    }
    printf("\n");
}

struct kassaeins* checkoutKassaeins(struct kassaeins* head)
{
    struct kassaeins* newHead = head->next;
    free(head);

    return newHead;
};

struct kassazwei* checkoutKassazwei(struct kassazwei* head)
{
    struct kassazwei* newHead = head->next;
    free(head);

    return newHead;
};

void freeall(struct person* personhead, struct kassaeins* einshead, struct kassazwei* zweihead)
{
    while(personhead != NULL)
    {
        struct person* temp = personhead->next;
        free(personhead);
        personhead = temp;
    }
    while(einshead != NULL)
    {
        struct kassaeins* temp = einshead->next;
        free(einshead->person);
        free(einshead);
        einshead = temp;
    }
    while(zweihead != NULL)
    {
        struct kassazwei* temp = zweihead->next;
        free(zweihead->person);
        free(zweihead);
        zweihead = temp;
    }
}

int main()
{
	// Lists here
	struct person* queue = NULL;
	struct kassaeins* kassaeins = NULL;
	struct kassazwei* kassazwei = NULL;

    while(42)
    {
        char n;
        system("CLS");
        printf("To add people to the queue, type their initials. If you are done enter '-'.\n");
        printf("Type any letter: ");
        scanf(" %c", &n);

        if(n == '-') break;

        // Add person
        queue = addLastQueue(queue, createPerson(n));
    }

    int run  = 1;
    while(run)
    {
        system("CLS");
        // Print here
        printQueue(queue);
        printKassaeins(kassaeins);
        printKassazwei(kassazwei);

        char c;
        printf("Enter (a) if you want the person in the front to queue at the next possible checkout.\n");
        printf("To check people out, type either (1) or (2) to check out the first person at the respective checkout.\n");
        printf("Type '-' if you want to exit the programme.\n");
        scanf(" %c", &c);

        if(c == '-') break;

        switch(c)
        {
        case '-':
            run = 0;
            break;
        case 'a':
            // anstellen
            if(getCountKassaeins(kassaeins) > getCountKassazwei(kassazwei))
            {
                kassazwei = addLastKassazwei(kassazwei, createKassazwei(queue));
            }
            else
            {
                kassaeins = addLastKassaeins(kassaeins, createKassaeins(queue));
            }
            queue = queue->next;
            break;
        case '1':
            // kassa1
            kassaeins = checkoutKassaeins(kassaeins);
            break;
        case '2':
            kassazwei = checkoutKassazwei(kassazwei);
            // kassa2
            break;
        }
    }

    // free list
    freeall(queue, kassaeins, kassazwei);

    return 0;
}
