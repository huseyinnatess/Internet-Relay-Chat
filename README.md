# Internet Relay Chat

## Proje Hakkında

`ft_irc`, Ecole 42 tarafından verilen bir projedir ve öğrencilerin **IRC (Internet Relay Chat)** sunucusu oluşturmasını amaçlar. Bu proje sayesinde temel ağ programlama ve iletişim protokolleri hakkında derinlemesine bilgi sahibi olacak, çok kullanıcılı bir sohbet ortamını sıfırdan inşa edeceksiniz.

IRC, metin tabanlı bir iletişim protokolüdür ve gerçek zamanlı grup sohbeti için yıllardır yaygın olarak kullanılmaktadır. Bu projede, belirli IRC komutlarını implemente ederek bir sunucu oluşturmanız beklenir.

## Proje Gereksinimleri

- **Dil**: C++
- **Protokol**: IRC RFC 1459 standardı baz alınmıştır.
- **Ağ**: TCP/IP kullanarak bir sunucu istemci ilişkisi oluşturulmalıdır.
- **Bağımlılıklar**: Standart kütüphanelerin dışında herhangi bir ek kütüphane kullanımı yasaktır.

## Özellikler

Bu projede implemente edilmesi gereken temel özellikler şunlardır:

- **Kullanıcı Girişi**:
  - `PASS`: Şifre belirleme.
  - `NICK`: Kullanıcı adı belirleme.
  - `USER`: Kullanıcı bilgilerini gönderme.

- **Kanal Yönetimi**:
  - `JOIN`: Kanal katılımı.
  - `PART`: Kanaldan ayrılma.
  - `KICK`: Kullanıcıyı kanaldan atma.
  - `TOPIC`: Kanal konusunu belirleme/değiştirme.
  - `MODE`: Kanal modlarını yönetme (örneğin: `+i`, `+k`, `+l`).

- **Özel Mesajlar**:
  - `PRIVMSG`: Özel mesaj gönderme.

- **Sunucu Yönetimi**:
  - `QUIT`: Kullanıcıyı IRC sunucusundan ayırma.
  - **Diğer**: Ek olarak kullanıcıların kanallara davet edilebilmesi (`INVITE`), sunucudan atılabilmesi ve mesajlaşma ile ilgili farklı komutlar da bulunmaktadır.

## Kurulum ve Kullanım

### Kurulum

1. Depoyu klonlayın:

   ```bash
   git clone https://github.com/kullanici-adiniz/ft_irc.git
