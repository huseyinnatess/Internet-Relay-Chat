# Internet Relay Chat

## [TR]

## Proje Hakkında

`ft_irc`, Ecole 42 tarafından verilen bir projedir ve öğrencilerin **IRC (Internet Relay Chat)** sunucusu oluşturmasını amaçlar. Bu proje sayesinde temel ağ programlama ve iletişim protokolleri hakkında derinlemesine bilgi sahibi olacak, çok kullanıcılı bir sohbet ortamını sıfırdan inşa edeceksiniz.

IRC, metin tabanlı bir iletişim protokolüdür ve gerçek zamanlı grup sohbeti için yıllardır yaygın olarak kullanılmaktadır. Bu projede, belirli IRC komutlarını implemente ederek bir sunucu oluşturmanız beklenir.

## Proje Gereksinimleri

- **Dil**: C++98
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
   git clone https://github.com/huseyinnatess/Ft_irc.git

2. Proje dizinine gidin:

   ```bash
   cd Ft_irc

3. Projeyi derleyin:

   ```bash
   make

4. Sunucuyu başlatın:

   ```bash
   ./ircserv <port> <password>

### Kullanım

1. İstemci tarafında, herhangi bir IRC istemcisi kullanarak sunucunuza bağlanabilirsiniz. Örneğin:

   ```bash
   /connect 127.0.0.1 <port>

2. Sunucuya bağlandıktan sonra, yukarıda bahsedilen komutları kullanarak kanallara katılabilir, mesajlaşabilir ve sunucu üzerinde farklı yönetimsel işlemler yapabilirsiniz.


