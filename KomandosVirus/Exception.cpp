#include "Exception.h"

Exception::Exception() { msg = "Niezidentyfikowny blad."; }
Exception::Exception(string message) { msg = message; }
void Exception::SetMessage(string message) { msg = message; }
string Exception::GetMessage() { return msg; }
