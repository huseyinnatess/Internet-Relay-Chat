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


## [EN]

# Internet Relay Chat

## About the Project

`ft_irc` is a project given by Ecole 42, aiming for students to create an **IRC (Internet Relay Chat)** server. Through this project, you will gain deep knowledge of basic network programming and communication protocols, while building a multi-user chat environment from scratch.

IRC is a text-based communication protocol that has been widely used for real-time group chat for many years. In this project, you are expected to implement certain IRC commands to create a server.

## Project Requirements

- **Language**: C++98
- **Protocol**: Based on the IRC RFC 1459 standard.
- **Network**: A server-client relationship should be established using TCP/IP.
- **Dependencies**: The use of external libraries, other than standard libraries, is prohibited.

## Features

The following core features must be implemented in this project:

- **User Login**:
  - `PASS`: Set a password.
  - `NICK`: Set a nickname.
  - `USER`: Send user information.

- **Channel Management**:
  - `JOIN`: Join a channel.
  - `PART`: Leave a channel.
  - `KICK`: Kick a user from the channel.
  - `TOPIC`: Set/Change the topic of a channel.
  - `MODE`: Manage channel modes (e.g., `+i`, `+k`, `+l`).

- **Private Messages**:
  - `PRIVMSG`: Send private messages.

- **Server Management**:
  - `QUIT`: Disconnect a user from the IRC server.
  - **Other**: Additional commands like inviting users to channels (`INVITE`), banning users from the server, and more related to messaging.

## Installation and Usage

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/huseyinnatess/Ft_irc.git

2. Navigate to the project directory:

   ```bash
   cd Ft_irc

3. Compile the project:

   ```bash
   make

4. Start the server:
   ```bash
   ./ircserv <port> <password>

### Usage

1. On the client side, you can connect to your server using any IRC client. For example:

   ```bash
   /connect 127.0.0.1 <port>

2. After connecting to the server, you can use the above commands to join channels, send messages, and perform various administrative tasks on the server.
