/* Copyright 2005-2011 Mark Dufour and contributors; License Expat (See LICENSE) */

/* Exceptions */

OSError::OSError(str *filename) {
    this->filename = filename;
    this->__class__ = cl_oserror;
    __ss_errno = errno;
    message = new str("");
    strerror = new str(::strerror(__ss_errno));
}
str *OSError::__str__() {
    return __add_strs(7, new str("[Errno "), __str(__ss_errno), new str("] "), strerror, new str(": '"), filename, new str("'"));
}
str *OSError::__repr__() {
    return __add_strs(5, new str("OSError("), __str(__ss_errno), new str(", '"), strerror, new str("')"));
}

IOError::IOError(str *filename) {
    this->filename = filename;
    this->__class__ = cl_ioerror;
    __ss_errno = errno;
    message = new str("");
    strerror = new str(::strerror(__ss_errno));
}
str *IOError::__str__() {
    return __add_strs(7, new str("[Errno "), __str(__ss_errno), new str("] "), strerror, new str(": '"), filename, new str("'"));
}
str *IOError::__repr__() {
    return __add_strs(5, new str("IOError("), __str(__ss_errno), new str(", '"), strerror, new str("')"));
}

