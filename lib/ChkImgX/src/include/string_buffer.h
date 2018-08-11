/*--------------------------------------------------------------------------
* C++ STLƒtƒŒƒ“ƒh‚È StringBuffer
* 
* created by Nekorabbit
*--------------------------------------------------------------------------*/
#pragma once

#ifndef UTL_STRING_BUFFER_H__
#define UTL_STRING_BUFFER_H__

#include <assert.h>
#include <sstream>

namespace utl {

template <typename CHAR>
class StringStreamBuffer : public std::basic_streambuf<CHAR> {
	typedef typename std::basic_string<CHAR> string_t;
public:
	StringStreamBuffer() : std::basic_streambuf<CHAR>() {
		buffer = NULL;
		offset = length = 0;
	}
	virtual ~StringStreamBuffer() {
		delete [] buffer; buffer = NULL;
		offset = length = 0;
	}

	void steal(string_t& dst) {
		size_t cur_pos = pptr() - buffer;
		dst.assign(buffer + offset, buffer + cur_pos);
		clear();
	}

	CHAR* pointer() { return buffer + offset; }
	size_t size() {
		size_t cur_pos = pptr() - buffer;
		return cur_pos - offset;
	}

	bool getline(CHAR* p, int len) {
		size_t cur_pos = pptr() - buffer;
		if(offset == cur_pos) {
			return false;
		}
		size_t line_end = cur_pos;
		size_t next_start = cur_pos;
		for(size_t i = offset; i < cur_pos; ++i) {
			if(buffer[i] == '\n') {
				line_end = i;
				next_start = i+1;
				break;
			}
			else if(buffer[i] == '\r') {
				line_end = i;
				if(i+1 < cur_pos && buffer[i+1] == '\n') {
					next_start = i+2;
				}
				else {
					next_start = i+1;
				}
				break;
			}
		}
		size_t copy_len = std::min<size_t>(len-1, line_end - offset);
		memcpy(p, buffer + offset, copy_len*sizeof(CHAR));
		p[copy_len] = '\0';
		offset = next_start;
		if(offset == cur_pos) {
			clear();
		}
		return true;
	}

	void clear() {
		offset = 0;
		setp(buffer, buffer + length);
	}

protected:
	virtual std::streamsize xsputn(const CHAR* s, std::streamsize n) {
		CHAR* dst = pptr();
		size_t cur_pos = dst - buffer;
		size_t remain_space = buffer + length - dst;
		if(remain_space < n) {
			grow(cur_pos + (size_t)n);
			dst = buffer + cur_pos;
			setp(dst, buffer + length);
		}
		memcpy(dst, s, (size_t)n*sizeof(CHAR));
		pbump((int)n);
		return n;
	}

	virtual int overflow(int c = EOF) {
		if(c != EOF) {
			size_t cur_pos = pptr() - buffer;
			assert(cur_pos == length);
			grow(length+1);
			buffer[cur_pos] = c;
			setp(buffer + cur_pos + 1, buffer + length);
		}
		return traits_type::to_int_type(c);
	}

private:
	void grow(size_t req_size) {
		size_t cur_pos = pptr() - buffer;
		size_t new_size = std::max<size_t>(32, length);
		while(req_size > new_size) new_size *= 2;
		CHAR* new_buffer = new CHAR[new_size]();
		memcpy(new_buffer, buffer, cur_pos*sizeof(CHAR));
		delete [] buffer;
		buffer = new_buffer;
		length = new_size;
	}

	CHAR* buffer;
	size_t offset;
	size_t length;
};

template <typename CHAR>
class StringBuffer : public std::basic_ostream<CHAR> {
	typedef typename std::basic_string<CHAR> string_t;
public:
	StringBuffer() : std::basic_ostream<CHAR>(&stream_buffer) { }
	void operator>>(string_t& dst) {
		stream_buffer.steal(dst);
	}
	bool getline(CHAR* p, int len) {
		return stream_buffer.getline(p, len);
	}
	size_t size() { return stream_buffer.size(); }
	CHAR* internal_pointer() { return stream_buffer.pointer(); }
	void clear() { stream_buffer.clear(); }
private:
	StringStreamBuffer<CHAR> stream_buffer;
};

// output target can be changed
template <typename CHAR>
class SharedStringBuffer {
	typedef typename std::basic_string<CHAR> string_t;
public:
	SharedStringBuffer() : target(NULL) { }
	void attach(StringBuffer<CHAR>* target__) {
		target = target__;
	}
	StringBuffer<CHAR>* detach() {
		auto ret = target;
		target = NULL;
		return ret;
	}
	template <typename value_t>
	std::basic_ostream<CHAR>& operator<<(const value_t& value) {
		*target << value;
		return *target;
	}
	void operator>>(string_t& dst) {
		if(target != NULL)
			*target >> dst;
	}
	bool getline(CHAR* p, int len) {
		if(target == NULL) return false;
		return target->getline(p, len);
	}
	void clear() {
		if(base != NULL) {
			target->clear();
		}
	}
private:
	StringBuffer<CHAR>* target;
};

} // namespace utl {

#endif // #ifndef UTL_STRING_BUFFER_H__
