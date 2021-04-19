#include<stdio.h>
#include<stdlib.h>

struct rehber{
  
  char isim[20];
  char soyisim[20];
  int yas;
  
  rehber *onceki,*sonraki;
  
};

rehber *ilk=NULL,*son=NULL,*gecici=NULL,*temp=NULL;//temp ve gecici yer değiştirmek veya sıralamak için kullandığım bazı pointerlar
FILE *dosya;// 


void sirali_ekle()
{  
  dosya=fopen("dosya.txt","r+");//dosyayı açtık.
  while(!feof(dosya))//dosyanın sonuna kadar dönen bir döndü tamıladık
  {
    gecici=(rehber*)malloc(sizeof(rehber));//her döngüde ram’dan bir yer ayırdık 
    gecici->sonraki=NULL;// son kutunun gösterdiği adresi boş atadık.
    fscanf(dosya,"%s %s %d",&gecici->isim,&gecici->soyisim,&gecici->yas);//dosyadan direkt olarak struct elelamlarına yazdık.		
    if(ilk==NULL) //ilk elemanı ekledik.
    {
      ilk=gecici;
      ilk->onceki=NULL;
      son=ilk;
    }
    
    else if(ilk->yas > gecici->yas)//eklenecek bir sonraki eleman ilk elemandan küçük mü ? 
                                               //küçükse ilk elemana onu atamamız gerekir çünkü küçükten büyüğe sıralama yapıyoruz.
          {
      ilk->onceki=gecici;
      gecici->sonraki=ilk;
      ilk=gecici;
      ilk->onceki=NULL;
    }
    
    else if(son->yas < gecici->yas)//eklenecek bir sonraki eleman son elemandan büyük mü ? 
                                               //büyükse son elemana onu atamamız gerekir çünkü küçükten büyüğe sıralama yapıyoruz.
    {
      son->sonraki=gecici;
      gecici->onceki=son;
      son=gecici;
    }
    
    else 
    {//
      temp=ilk;//gezici pointer olarak kullandık
      while(temp->sonraki!=NULL)//son elemanı dahil etmedim çünkü "temp->sonraki->yas" kriterini sağlamıyor 
      {                         //son elemandan sonra eleman olmadığı için.
        if(temp->yas < gecici->yas && gecici->yas < temp->sonraki->yas )//eğer ekelenecek eleman arada ise nereye ekleneceğini bulup 
        {                                                               // oraya ekleme yapacağız.
          temp->sonraki->onceki=gecici;
          gecici->sonraki=temp->sonraki;
          gecici->onceki=temp;
          temp->sonraki=gecici;break;
        }
        temp=temp->sonraki;// her seferinde bir sonraki kutuya erişim sağlamak için.
      }
    }
  }
  fclose(dosya);//dosyayı kapattık.
  return ;
}

int listele(int i)
{
  if(i==1)//fonksiyona gelen değer 1 ise bastan sona sıralama yapacak
  {
    gecici=ilk;
    while(gecici!=NULL)
    {
      printf("%d\n",gecici->no);
      gecici=gecici->sonraki;
    }
    return 0;
  }
  
  else if(i==0) //0 değeri gelmişse sondan başa gelecek
  {
    gecici=son;
    while(gecici!=NULL)
    {
      printf("%d\n",gecici->no);
      gecici=gecici->onceki;
    }
    
  }
  
  return 0 ;	
}

int main(){

    sirali_ekle();,
    printf("Başarıyla Eklendi Listeleniyor...\n\n");
    listele(1);
    return 0;
}
