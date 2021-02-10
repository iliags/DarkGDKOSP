netHttpRequestHeader(netHttpRequestPacket, 'GET http://' + netHttpRequestHostname + netHttpRequestPage + ' HTTP/1.0\r\n');
netHttpRequestHeader(netHttpRequestPacket, 'Accept: */*\r\n');
netHttpRequestHeader(netHttpRequestPacket, 'Accept-Language: en-us\r\n');
netHttpRequestHeader(netHttpRequestPacket, 'UA-CPU: x86\r\n');
netHttpRequestHeader(netHttpRequestPacket, 'Accept-Encoding: gzip, deflate\r\n');
netHttpRequestHeader(netHttpRequestPacket, 'User-Agent: S3GE HTTP\r\n');
netHttpRequestHeader(netHttpRequestPacket, 'Host: ' + netHttpRequestHostname );
netHttpRequestHeader(netHttpRequestPacket, 'Connection: Keep-Alive\r\n');
netHttpRequestHeader(netHttpRequestPacket, '');
