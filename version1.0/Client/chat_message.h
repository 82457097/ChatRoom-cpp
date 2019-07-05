#pragma once
#include"struct_header.h"
#include<cstdlib>
#include<cassert>
#include<cstring>

class chat_message {
public:
	enum { header_length = sizeof(Header) };
	enum { max_body_length = 512 };

	chat_message() {}

	const char *data() const { return data_; }

	char *data() { return data_; }

	std::size_t length() const { return header_length + m_header.bodySize; }

	const char *body() const { return data_ + header_length; }

	char *body() { return data_ + header_length; }

	int type() const { return m_header.type; }

	std::size_t body_length() const { return m_header.bodySize; }
	
	void setMessage(int messageType, const void *buffer, size_t bufferSize) {
		assert(bufferSize <= max_body_length);
		m_header.bodySize = bufferSize;
		m_header.type = messageType;
		std::memcpy(body(), buffer, bufferSize);
		std::memcpy(data(), &m_header, sizeof(m_header));
	}

	bool decode_header() {
		std::memcpy(&m_header,data(), header_length);
		if (m_header.bodySize > max_body_length) {
			std::cout << "body size " << m_header.bodySize << " " << m_header.type << std::endl;
			return false;
		}
		return true;
	}

private:
	char data_[header_length + max_body_length];
	Header m_header;
};