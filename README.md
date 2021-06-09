# ESP MQTT TLS ECC Client
## Exploring TLS: Modified HTTPS Request Example

Uses APIs from `esp-tls` component to make a very simple HTTPS request over a secure connection, including verifying the server TLS certificate.
### keygen
openssl req -newkey rsa:2048 -new -nodes -x509 -days 3650 -keyout key.pem -subj "/C=DE/ST=b/L=B/CN=192.168.178.25" -out cert.pem

### Run HTTPS server
provide simple index.html, key.pem and cert.pem. then call
npx http-server -S -C cert.pem

### Turn on Debug Messages
menuconfig -> component -> mbedtls -> enable debug vebrose

### Verbose Debug Log HTTPS Request 

I (18031) mbedtls: ssl_cli.c:3785 client state: 0

I (18031) mbedtls: ssl_tls.c:2847 => flush output

I (18041) mbedtls: ssl_tls.c:2859 <= flush output

I (18041) mbedtls: ssl_cli.c:3785 client state: 1

I (18051) mbedtls: ssl_tls.c:2847 => flush output

I (18051) mbedtls: ssl_tls.c:2859 <= flush output

I (18061) mbedtls: ssl_cli.c:805 => write client hello

I (18071) mbedtls: ssl_tls.c:3286 => write handshake message

I (18071) mbedtls: ssl_tls.c:3445 => write record

I (18081) mbedtls: ssl_tls.c:2847 => flush output

I (18081) mbedtls: ssl_tls.c:2866 message length: 243, out_left: 243

I (18091) mbedtls: ssl_tls.c:2871 ssl->f_send() returned 243 (-0xffffff0d)

I (18101) mbedtls: ssl_tls.c:2899 <= flush output

I (18101) mbedtls: ssl_tls.c:3578 <= write record

I (18111) mbedtls: ssl_tls.c:3422 <= write handshake message

I (18111) mbedtls: ssl_cli.c:1255 <= write client hello

I (18121) mbedtls: ssl_cli.c:3785 client state: 2

I (18131) mbedtls: ssl_tls.c:2847 => flush output

I (18131) mbedtls: ssl_tls.c:2859 <= flush output

I (18141) mbedtls: ssl_cli.c:1684 => parse server hello

I (18141) mbedtls: ssl_tls.c:4419 => read record

I (18151) mbedtls: ssl_tls.c:2628 => fetch input

I (18151) mbedtls: ssl_tls.c:2789 in_left: 0, nb_want: 5

I (18161) mbedtls: ssl_tls.c:2813 in_left: 0, nb_want: 5

I (18171) mbedtls: ssl_tls.c:2814 ssl->f_recv(_timeout)() returned 5 (-0xfffffffb)

I (18171) mbedtls: ssl_tls.c:2834 <= fetch input

I (18181) mbedtls: ssl_tls.c:2628 => fetch input

I (18191) mbedtls: ssl_tls.c:2789 in_left: 5, nb_want: 70

I (18191) mbedtls: ssl_tls.c:2813 in_left: 5, nb_want: 70

I (18201) mbedtls: ssl_tls.c:2814 ssl->f_recv(_timeout)() returned 65 (-0xffffffbf)

I (18211) mbedtls: ssl_tls.c:2834 <= fetch input

I (18211) mbedtls: ssl_tls.c:4493 <= read record

I (18221) mbedtls: ssl_cli.c:2000 server hello, total extension length: 21

I (18231) mbedtls: ssl_cli.c:2200 <= parse server hello

I (18231) mbedtls: ssl_cli.c:3785 client state: 3

I (18241) mbedtls: ssl_tls.c:2847 => flush output

I (18241) mbedtls: ssl_tls.c:2859 <= flush output

I (18251) mbedtls: ssl_tls.c:5763 => parse certificate

I (18251) mbedtls: ssl_tls.c:4419 => read record

I (18261) mbedtls: ssl_tls.c:2628 => fetch input

I (18271) mbedtls: ssl_tls.c:2789 in_left: 0, nb_want: 5

I (18271) mbedtls: ssl_tls.c:2813 in_left: 0, nb_want: 5

I (18281) mbedtls: ssl_tls.c:2814 ssl->f_recv(_timeout)() returned 5 (-0xfffffffb)

I (18291) mbedtls: ssl_tls.c:2834 <= fetch input

I (18291) mbedtls: ssl_tls.c:2628 => fetch input

I (18301) mbedtls: ssl_tls.c:2789 in_left: 5, nb_want: 880

I (18301) mbedtls: ssl_tls.c:2813 in_left: 5, nb_want: 880

I (18311) mbedtls: ssl_tls.c:2814 ssl->f_recv(_timeout)() returned 875 (-0xfffffc95)

I (18321) mbedtls: ssl_tls.c:2834 <= fetch input

I (18331) mbedtls: ssl_tls.c:4493 <= read record

I (18341) mbedtls: ssl_tls.c:5971 <= parse certificate

I (18341) mbedtls: ssl_cli.c:3785 client state: 4

I (18341) mbedtls: ssl_tls.c:2847 => flush output

I (18351) mbedtls: ssl_tls.c:2859 <= flush output

I (18351) mbedtls: ssl_cli.c:2566 => parse server key exchange

I (18361) mbedtls: ssl_tls.c:4419 => read record

I (18361) mbedtls: ssl_tls.c:2628 => fetch input

I (18371) mbedtls: ssl_tls.c:2789 in_left: 0, nb_want: 5

I (18381) mbedtls: ssl_tls.c:2813 in_left: 0, nb_want: 5

I (18381) mbedtls: ssl_tls.c:2814 ssl->f_recv(_timeout)() returned 5 (-0xfffffffb)

I (18391) mbedtls: ssl_tls.c:2834 <= fetch input

I (18401) mbedtls: ssl_tls.c:2628 => fetch input

I (18401) mbedtls: ssl_tls.c:2789 in_left: 5, nb_want: 338

I (18411) mbedtls: ssl_tls.c:2813 in_left: 5, nb_want: 338

I (18411) mbedtls: ssl_tls.c:2814 ssl->f_recv(_timeout)() returned 333 (-0xfffffeb3)

I (18421) mbedtls: ssl_tls.c:2834 <= fetch input

I (18431) mbedtls: ssl_tls.c:4493 <= read record

I (18441) mbedtls: ssl_cli.c:2268 ECDH curve: secp256r1

I (18441) mbedtls: ssl_cli.c:2507 Server used SignatureAlgorithm 1

I (18451) mbedtls: ssl_cli.c:2509 Server used HashAlgorithm 4

I (18481) mbedtls: ssl_cli.c:2926 <= parse server key exchange

I (18481) mbedtls: ssl_cli.c:3785 client state: 5

I (18481) mbedtls: ssl_tls.c:2847 => flush output

I (18491) mbedtls: ssl_tls.c:2859 <= flush output

I (18491) mbedtls: ssl_cli.c:2959 => parse certificate request

I (18501) mbedtls: ssl_tls.c:4419 => read record

I (18511) mbedtls: ssl_tls.c:2628 => fetch input

I (18511) mbedtls: ssl_tls.c:2789 in_left: 0, nb_want: 5

I (18521) mbedtls: ssl_tls.c:2813 in_left: 0, nb_want: 5

I (18521) mbedtls: ssl_tls.c:2814 ssl->f_recv(_timeout)() returned 5 (-0xfffffffb)

I (18531) mbedtls: ssl_tls.c:2834 <= fetch input

I (18541) mbedtls: ssl_tls.c:2628 => fetch input

I (18541) mbedtls: ssl_tls.c:2789 in_left: 5, nb_want: 9

I (18551) mbedtls: ssl_tls.c:2813 in_left: 5, nb_want: 9

I (18561) mbedtls: ssl_tls.c:2814 ssl->f_recv(_timeout)() returned 4 (-0xfffffffc)

I (18561) mbedtls: ssl_tls.c:2834 <= fetch input

I (18571) mbedtls: ssl_tls.c:4493 <= read record

I (18571) mbedtls: ssl_cli.c:3115 <= parse certificate request

I (18581) mbedtls: ssl_cli.c:3785 client state: 6

I (18591) mbedtls: ssl_tls.c:2847 => flush output

I (18591) mbedtls: ssl_tls.c:2859 <= flush output

I (18601) mbedtls: ssl_cli.c:3125 => parse server hello done

I (18601) mbedtls: ssl_tls.c:4419 => read record

I (18611) mbedtls: ssl_tls.c:4489 reuse previously read message

I (18621) mbedtls: ssl_tls.c:4493 <= read record

I (18621) mbedtls: ssl_cli.c:3155 <= parse server hello done

I (18631) mbedtls: ssl_cli.c:3785 client state: 7

I (18631) mbedtls: ssl_tls.c:2847 => flush output

I (18641) mbedtls: ssl_tls.c:2859 <= flush output

I (18651) mbedtls: ssl_tls.c:5437 => write certificate

I (18651) mbedtls: ssl_tls.c:5454 <= skip write certificate

I (18661) mbedtls: ssl_cli.c:3785 client state: 8

I (18661) mbedtls: ssl_tls.c:2847 => flush output

I (18671) mbedtls: ssl_tls.c:2859 <= flush output

I (18671) mbedtls: ssl_cli.c:3167 => write client key exchange

I (19411) mbedtls: ssl_tls.c:3286 => write handshake message

I (19411) mbedtls: ssl_tls.c:3445 => write record

I (19411) mbedtls: ssl_tls.c:2847 => flush output

I (19421) mbedtls: ssl_tls.c:2866 message length: 75, out_left: 75

I (19431) mbedtls: ssl_tls.c:2871 ssl->f_send() returned 75 (-0xffffffb5)

I (19431) mbedtls: ssl_tls.c:2899 <= flush output

I (19441) mbedtls: ssl_tls.c:3578 <= write record

I (19451) mbedtls: ssl_tls.c:3422 <= write handshake message

I (19451) mbedtls: ssl_cli.c:3444 <= write client key exchange

I (19461) mbedtls: ssl_cli.c:3785 client state: 9

I (19461) mbedtls: ssl_tls.c:2847 => flush output

I (19471) mbedtls: ssl_tls.c:2859 <= flush output

I (19481) mbedtls: ssl_cli.c:3496 => write certificate verify

I (19481) mbedtls: ssl_tls.c:653 => derive keys

I (19491) mbedtls: ssl_tls.c:1228 => calc verify sha256

I (19491) mbedtls: ssl_tls.c:1234 <= calc verify

I (19511) mbedtls: ssl_tls.c:1139 <= derive keys

I (19511) mbedtls: ssl_cli.c:3525 <= skip write certificate verify

I (19511) mbedtls: ssl_cli.c:3785 client state: 10

I (19521) mbedtls: ssl_tls.c:2847 => flush output

I (19521) mbedtls: ssl_tls.c:2859 <= flush output

I (19531) mbedtls: ssl_tls.c:5987 => write change cipher spec

I (19531) mbedtls: ssl_tls.c:3286 => write handshake message

I (19541) mbedtls: ssl_tls.c:3445 => write record

I (19551) mbedtls: ssl_tls.c:2847 => flush output

I (19551) mbedtls: ssl_tls.c:2866 message length: 6, out_left: 6

I (19561) mbedtls: ssl_tls.c:2871 ssl->f_send() returned 6 (-0xfffffffa)

I (19571) mbedtls: ssl_tls.c:2899 <= flush output

I (19571) mbedtls: ssl_tls.c:3578 <= write record

I (19581) mbedtls: ssl_tls.c:3422 <= write handshake message

I (19581) mbedtls: ssl_tls.c:6001 <= write change cipher spec

I (19591) mbedtls: ssl_cli.c:3785 client state: 11

I (19601) mbedtls: ssl_tls.c:2847 => flush output

I (19601) mbedtls: ssl_tls.c:2859 <= flush output

I (19611) mbedtls: ssl_tls.c:6515 => write finished

I (19611) mbedtls: ssl_tls.c:6331 => calc  finished tls sha256

I (19621) mbedtls: ssl_tls.c:6361 <= calc  finished

I (19631) mbedtls: ssl_tls.c:3286 => write handshake message

I (19631) mbedtls: ssl_tls.c:3445 => write record

I (19641) mbedtls: ssl_tls.c:1446 => encrypt buf

I (19641) mbedtls: ssl_tls.c:1780 <= encrypt buf

I (19651) mbedtls: ssl_tls.c:2847 => flush output

I (19651) mbedtls: ssl_tls.c:2866 message length: 45, out_left: 45

I (19671) mbedtls: ssl_tls.c:2871 ssl->f_send() returned 45 (-0xffffffd3)

I (19671) mbedtls: ssl_tls.c:2899 <= flush output

I (19671) mbedtls: ssl_tls.c:3578 <= write record

I (19681) mbedtls: ssl_tls.c:3422 <= write handshake message

I (19691) mbedtls: ssl_tls.c:6624 <= write finished

I (19691) mbedtls: ssl_cli.c:3785 client state: 12

I (19701) mbedtls: ssl_tls.c:2847 => flush output

I (19701) mbedtls: ssl_tls.c:2859 <= flush output

I (19711) mbedtls: ssl_cli.c:3676 => parse new session ticket

I (19721) mbedtls: ssl_tls.c:4419 => read record

I (19721) mbedtls: ssl_tls.c:2628 => fetch input

I (19731) mbedtls: ssl_tls.c:2789 in_left: 0, nb_want: 5

I (19731) mbedtls: ssl_tls.c:2813 in_left: 0, nb_want: 5

I (19741) mbedtls: ssl_tls.c:2814 ssl->f_recv(_timeout)() returned 5 (-0xfffffffb)

I (19751) mbedtls: ssl_tls.c:2834 <= fetch input

I (19751) mbedtls: ssl_tls.c:2628 => fetch input

I (19761) mbedtls: ssl_tls.c:2789 in_left: 5, nb_want: 207

I (19771) mbedtls: ssl_tls.c:2813 in_left: 5, nb_want: 207

I (19771) mbedtls: ssl_tls.c:2814 ssl->f_recv(_timeout)() returned 202 (-0xffffff36)

I (19781) mbedtls: ssl_tls.c:2834 <= fetch input

I (19791) mbedtls: ssl_tls.c:4493 <= read record

I (19791) mbedtls: ssl_cli.c:3769 <= parse new session ticket

I (19801) mbedtls: ssl_cli.c:3785 client state: 12

I (19801) mbedtls: ssl_tls.c:2847 => flush output

I (19811) mbedtls: ssl_tls.c:2859 <= flush output

I (19811) mbedtls: ssl_tls.c:6010 => parse change cipher spec

I (19821) mbedtls: ssl_tls.c:4419 => read record

I (19831) mbedtls: ssl_tls.c:2628 => fetch input

I (19831) mbedtls: ssl_tls.c:2789 in_left: 0, nb_want: 5

I (19841) mbedtls: ssl_tls.c:2813 in_left: 0, nb_want: 5

I (19841) mbedtls: ssl_tls.c:2814 ssl->f_recv(_timeout)() returned 5 (-0xfffffffb)

I (19851) mbedtls: ssl_tls.c:2834 <= fetch input

I (19861) mbedtls: ssl_tls.c:2628 => fetch input

I (19861) mbedtls: ssl_tls.c:2789 in_left: 5, nb_want: 6

I (19871) mbedtls: ssl_tls.c:2813 in_left: 5, nb_want: 6

I (19881) mbedtls: ssl_tls.c:2814 ssl->f_recv(_timeout)() returned 1 (-0xffffffff)

I (19881) mbedtls: ssl_tls.c:2834 <= fetch input

I (19891) mbedtls: ssl_tls.c:4493 <= read record

I (19891) mbedtls: ssl_tls.c:6074 <= parse change cipher spec

I (19901) mbedtls: ssl_cli.c:3785 client state: 13

I (19911) mbedtls: ssl_tls.c:2847 => flush output

I (19911) mbedtls: ssl_tls.c:2859 <= flush output

I (19921) mbedtls: ssl_tls.c:6641 => parse finished

I (19921) mbedtls: ssl_tls.c:6331 => calc  finished tls sha256

I (19931) mbedtls: ssl_tls.c:6361 <= calc  finished

I (19941) mbedtls: ssl_tls.c:4419 => read record

I (19941) mbedtls: ssl_tls.c:2628 => fetch input

I (19951) mbedtls: ssl_tls.c:2789 in_left: 0, nb_want: 5

I (19951) mbedtls: ssl_tls.c:2813 in_left: 0, nb_want: 5

I (19961) mbedtls: ssl_tls.c:2814 ssl->f_recv(_timeout)() returned 5 (-0xfffffffb)

I (19971) mbedtls: ssl_tls.c:2834 <= fetch input

I (19971) mbedtls: ssl_tls.c:2628 => fetch input

I (19981) mbedtls: ssl_tls.c:2789 in_left: 5, nb_want: 45

I (19991) mbedtls: ssl_tls.c:2813 in_left: 5, nb_want: 45

I (19991) mbedtls: ssl_tls.c:2814 ssl->f_recv(_timeout)() returned 40 (-0xffffffd8)

I (20001) mbedtls: ssl_tls.c:2834 <= fetch input

I (20011) mbedtls: ssl_tls.c:1943 => decrypt buf

I (20011) mbedtls: ssl_tls.c:2468 <= decrypt buf

I (20021) mbedtls: ssl_tls.c:4493 <= read record

I (20021) mbedtls: ssl_tls.c:6709 <= parse finished

I (20031) mbedtls: ssl_cli.c:3785 client state: 14

I (20031) mbedtls: ssl_tls.c:2847 => flush output

I (20041) mbedtls: ssl_tls.c:2859 <= flush output

I (20041) mbedtls: ssl_cli.c:3896 handshake: done

I (20051) mbedtls: ssl_cli.c:3785 client state: 15

I (20061) mbedtls: ssl_tls.c:2847 => flush output

I (20061) mbedtls: ssl_tls.c:2859 <= flush output

I (20071) mbedtls: ssl_tls.c:8213 <= handshake

I (20071) example: Connection established...
I (20081) mbedtls: ssl_tls.c:8805 => write

I (20081) mbedtls: ssl_tls.c:3445 => write record

I (20091) mbedtls: ssl_tls.c:1446 => encrypt buf

I (20091) mbedtls: ssl_tls.c:1780 <= encrypt buf

I (20101) mbedtls: ssl_tls.c:2847 => flush output

I (20101) mbedtls: ssl_tls.c:2866 message length: 126, out_left: 126

I (20111) mbedtls: ssl_tls.c:2871 ssl->f_send() returned 126 (-0xffffff82)

I (20121) mbedtls: ssl_tls.c:2899 <= flush output

I (20121) mbedtls: ssl_tls.c:3578 <= write record

I (20131) mbedtls: ssl_tls.c:8833 <= write

I (20131) example: 97 bytes written
I (20141) example: Reading HTTPS response...
I (20141) mbedtls: ssl_tls.c:8389 => read

I (20151) mbedtls: ssl_tls.c:4419 => read record

I (20151) mbedtls: ssl_tls.c:2628 => fetch input

I (20161) mbedtls: ssl_tls.c:2789 in_left: 0, nb_want: 5

I (20171) mbedtls: ssl_tls.c:2813 in_left: 0, nb_want: 5

I (20171) mbedtls: ssl_tls.c:2814 ssl->f_recv(_timeout)() returned 5 (-0xfffffffb)

I (20181) mbedtls: ssl_tls.c:2834 <= fetch input

I (20191) mbedtls: ssl_tls.c:2628 => fetch input

I (20191) mbedtls: ssl_tls.c:2789 in_left: 5, nb_want: 459

I (20201) mbedtls: ssl_tls.c:2813 in_left: 5, nb_want: 459

I (20201) mbedtls: ssl_tls.c:2814 ssl->f_recv(_timeout)() returned 454 (-0xfffffe3a)

I (20211) mbedtls: ssl_tls.c:2834 <= fetch input

I (20221) mbedtls: ssl_tls.c:1943 => decrypt buf

I (20231) mbedtls: ssl_tls.c:2468 <= decrypt buf

I (20231) mbedtls: ssl_tls.c:4493 <= read record

I (20231) mbedtls: ssl_tls.c:8681 <= read

HTTP/1.1 200 OK
server: ecstatic-3.3.2
cache-control: max-age=3600
last-modified: Wed, 09 Jun 2021 10:16:09 GMT
etag: W/"15084206-146-2021-06-09T10:16:09.296Z"
content-length: 146
content-type: text/html; charset=UTF-8
Date: Wed, 09 Jun 2021 18:45:07 GMT
Connection: close

<!DOCTYPE html>
<html>
    <head>
        <title>Example</title>
    </head>
    <body>
        <p>Hello World Paragraph!</p>
    </body>
</html>
I (20281) mbedtls: ssl_tls.c:8389 => read

I (20281) mbedtls: ssl_tls.c:4419 => read record

I (20291) mbedtls: ssl_tls.c:2628 => fetch input

I (20291) mbedtls: ssl_tls.c:2789 in_left: 0, nb_want: 5

I (20301) mbedtls: ssl_tls.c:2813 in_left: 0, nb_want: 5

I (20311) mbedtls: ssl_tls.c:2814 ssl->f_recv(_timeout)() returned 5 (-0xfffffffb)

I (20311) mbedtls: ssl_tls.c:2834 <= fetch input

I (20321) mbedtls: ssl_tls.c:2628 => fetch input

I (20331) mbedtls: ssl_tls.c:2789 in_left: 5, nb_want: 31

I (20331) mbedtls: ssl_tls.c:2813 in_left: 5, nb_want: 31

I (20341) mbedtls: ssl_tls.c:2814 ssl->f_recv(_timeout)() returned 26 (-0xffffffe6)

I (20351) mbedtls: ssl_tls.c:2834 <= fetch input

I (20351) mbedtls: ssl_tls.c:1943 => decrypt buf

I (20361) mbedtls: ssl_tls.c:2468 <= decrypt buf

I (20361) mbedtls: ssl_tls.c:5278 got an alert message, type: [1:0]

I (20371) mbedtls: ssl_tls.c:5293 is a close notify message
