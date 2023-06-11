#include <stdio.h>


typedef struct{
    unsigned int size:31; // 31 bit size tutmak icin
    unsigned int free:1; // 1 bit free durumu icin
} info;

int *heap_start;
int *heap_end;

initheap(){
    heap_start = sbrk(0);
    heap_end = sbrk(1024);
}

void *mymalloc(int size){
    static int start = 0;
    if(!start){
        start = 1;
        initheap();
    }

    info *block = heap_start;
    while(block < heap_end && block->free == 1 && block->size < size){
        /* bir sonraki block bulma*/
        block = (info *)((char*)block + sizeof(info) + block->size) + sizeof(info);
        /* byte ile işlem yaptığımız için block'u
        char pointer'a çevirdik. 1 yer kapliyor cünkü char
        int olsaydi 4 4 ilerlerdi
        
        sizeof(info) = free olup olmadığını gosteren
        en baştaki 1 bit

        block->size = alanın geriye kalan kısmını gösterir
        */

       /** 
        * *updated 11.06.2023 18:03
        * sonradan eklenen sizeof(info), blokların
        * sonunda bulunan free durumu icin bittir.
       */
    }
    if(block < heap_end){
        split(block, size); /* kullanıcıya verdigimiz alan haricindeki
        alani tutmak icin*/

        block->free = 1;
        block->size = size; /* kullanıcının istediği kadar 
        size vermek icin*/

        info *temp = (info *)((char *)block + size +sizeof(info));
        temp->free = 1;
        temp->size = size;
        /** blogun sonunu bulmak icin*/

        return (char *)block + sizeof(info);   

    }
}

int *split(info *block, int size){
    info *starttag = block;
    info *b = (char *)block + sizeof(info) + size;
    /* yeni bloğun baslangic adresi */
    b->free = 0;
    b->size = block->size - size - 2*sizeof(info);

    info *endtag = (char *)block + sizeof(info) + size;
    
    endtag->free = 0;
    endtag->size = starttag->size;

    return b;
}

int myfree(void *ptr){
    info *b = (info *)((char *)ptr - sizeof(info)); /*blogun basina kaymis olur*/
    b->free = 1;
    
    /** coalescing:
     * iki tane free olan blogun arasindaki allocated
     * memory yi free ettiğimizi düşünelim. o zaman
     * art arda 3 free memory blogu olur. bulunduğumuz
     * blogu ve bloktan sonraki ya da önceki blokla 
     * birlestirmek lazim. bu isleme coalescing denir.
    */

    info *nextb = (char *) ptr + b->size;
    if(nextb->free == 1){ /** bir sonraki block bos ise*/
        coalescing(b, nextb);
    }

    info *prevb = (info *)((char *) ptr - sizeof(info));
    /**bir onceki blogun sonu*/
    if(prevb->free == 1){
        info *temp = (info *)((char *)prevb - (prevb->size + sizeof(info)));
        /** bir onceki blogun basi*/
        coalescing(b, temp);
    }

}

info *coalescing(info *b, info *nextb){
    b->size += nextb->size;
}

int main(void){
    info a;
    a.free = 1;
    a.size = 128;
    
    printf("size: %d - %d - %d \n", sizeof(info), a.size, a.free);

    int *arr = (int *)mymalloc(sizeof(int)*100);
    myfree(arr); /** alani free etme*/
}
