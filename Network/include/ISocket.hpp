#pragma once

#include <string>
#include <vector>

class ISocket {

protected:

	unsigned int	_id;
	std::string		_address;
	int				_port;

public:

	ISocket() {}
	virtual				~ISocket() {}
	virtual void		prepareToConnect() = 0;
	virtual void		getNewConnections(std::vector<unsigned int> &clients) = 0;
	virtual void		startReceivingConnections() = 0;
	virtual void		sendRequest(std::vector<char> const &data, unsigned int const &id) = 0;
	virtual void		sendRequest(std::vector<char> const &data) = 0;
	virtual void		receiveRequest(std::vector<char> &data, unsigned int &size, unsigned int &id) = 0;
	virtual void		receiveRequest(std::vector<char> &data, unsigned int &size) = 0;
	virtual void		registerAddress(std::string const &addr) = 0;
	virtual void		registerPort(int const &val) = 0;

};