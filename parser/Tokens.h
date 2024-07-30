#pragma once
#include <iostream>
#include <vector>
#include <string_view>

enum class TokenKind
{
	tkOPERATOR_ADD,//+
	tkOPERATOR_DIF,//-
	tkOPERATOR_DIV,// "/"
	tkOPERATOR_MULT,//*
	tkOPERATOR_DEG,// ^
	tkBRACKET_LEFT, // "(" 
	tkBRACKET_RIGHT, // ")"
	tkNUMBER,
	tkUndef,
	tkEND
};

struct Token {
	Token(std::string& lexeme, TokenKind kind) : token{ lexeme }, id{ kind }{} //копирование
	Token(std::string&& lexemе, TokenKind kind) : token(lexemе), id(kind){} //перемещение 
	Token(TokenKind tk) : token{""}, id{tk} {} //для tkEND

	std::string token; // лексема
	TokenKind id;
};
 
class Lexer
{
public:
	Lexer() = default;

	Lexer(std::string& str) {
		ReadToken(str);
	}

	static const Token END;

private:
	TokenKind GetKind(char ch)
	{
		switch (ch)
		{
		case '+':
			return TokenKind::tkOPERATOR_ADD;
			break;
		case '-':
			return TokenKind::tkOPERATOR_DIF;
			break;
		case '/':
			return TokenKind::tkOPERATOR_DIV;
			break;
		case '*':
			return TokenKind::tkOPERATOR_MULT;
			break;
		case '^':
			return TokenKind::tkOPERATOR_DEG;
			break;
		case '(':
			return TokenKind::tkBRACKET_LEFT;
			break;
		case ')':
			return TokenKind::tkBRACKET_RIGHT;
			break;
		default:
			return (ch>='0' && ch<='9' ? TokenKind::tkNUMBER : TokenKind::tkUndef);
			break;
		}
	}

	bool isWhiteSpace(char ch)
	{
		return (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t');
	}

	size_t LookNumber(std::string_view m_buf)
	{
		size_t count = 0;

		while (count < m_buf.size())
		{
			if (GetKind(m_buf[count]) != TokenKind::tkNUMBER)
				break;
			count++;
		}

		return count;
	   
	}

	bool isOperator(TokenKind& kind) {
		if (kind == TokenKind::tkOPERATOR_ADD ||
			kind == TokenKind::tkOPERATOR_DEG ||
			kind == TokenKind::tkOPERATOR_DIF ||
			kind == TokenKind::tkOPERATOR_DIV ||
			kind == TokenKind::tkOPERATOR_MULT) return true;
		else return false;
	}

	void ReadToken(std::string_view m_buf)//(std::string_view m_buf) 
	{	
		if (m_buf.empty())
			return;

		while (!m_buf.empty())
		{
			auto ch = m_buf.front();//достали первый символ 
			TokenKind kind = GetKind(ch);

			if (isWhiteSpace(ch)) //пробел
			{
				m_buf.remove_prefix(1);
				continue;
			}
			 
			if (kind == TokenKind::tkNUMBER) { //число
				auto cnt = LookNumber(m_buf);
				auto str = m_buf.substr(0, cnt);
				
				m_tokens.emplace_back(std::string{ std::begin(str), std::end(str) }, kind);
				m_buf.remove_prefix(cnt);
				continue;
			}

			if (kind == TokenKind::tkUndef) continue; //мусор
	

			auto str = m_buf.substr(0, 1); //операнд и скобки
			m_tokens.emplace_back(std::string{ str.begin(), str.end() }, kind);
			m_buf.remove_prefix(1);
			
		}

	}

	TokenKind WatchTokenId(){ //посмотреть токен и вернуть его id						std::vector<Token>& m_tokens
		return m_tokens[m_curPos].id;
	}

	Token ReturnToken() { //вернуть весь токен (лексему + id)
		if (m_curPos < m_tokens.size()) {
			return m_tokens[m_curPos];
		}
		else {
			return  END;
		}
		m_curPos++;
	}
	
//private:
	std::vector<Token> m_tokens{};
	size_t m_curPos{ 0 };

};
const Token Lexer::END = Token(TokenKind::tkEND);

//class Token {
//	Token(TokenType::token) {};
//
//	TokenType Type() const { return TokenType::token; }
//};







			//if (isOperator(kind)) {
			//	auto str = m_buf.substr(0, 1); //операнд
			//	m_tokens.emplace_back(std::string{ str.begin(), str.end() }, kind);
			//	m_buf.remove_prefix(1);
			//	continue;
			//}

			//if (kind == TokenKind::tkBRACKET_LEFT || kind == TokenKind::tkBRACKET_RIGHT) {
			//	auto str = m_buf.substr(0, 1); // "(" , ")"
			//	m_tokens.emplace_back(std::string{ str.begin(), str.end() }, kind);
			//	m_buf.remove_prefix(1);
			//	continue;
			//}