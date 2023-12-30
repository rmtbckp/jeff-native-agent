#include "Object.hpp"

#include "common.hpp"
#include "jni.hpp"
#include "jvmti.hpp"
#include "Type.hpp"

#include <boost/format.hpp>

using namespace std;
using namespace boost;
using namespace jeff;

Object::Object() : type(nullptr), to_string(string()) {
    // Empty
}

Object::Object(const Type *const type, std::string to_string)
        : type(type), to_string(to_string) {
    // Empty
}

Object::~Object() {
    delete type;
}

const Type Object::getType() const {
    return *type;
}

const string Object::toString() const {
    return to_string;
}

unique_ptr<Object> Object::from(jvmtiEnv &jvmti, JNIEnv &jni, jbooleanArray array, string signature) {
    list<bool> values = to_list(jni, array);
    string as_string = join(values, [](string a, string b) -> string { return a + ", " + b; });

    Object *ret = new Object(Type::from(jvmti, jni, signature), as_string);
    return unique_ptr<Object>(ret);
}

unique_ptr<Object> Object::from(jvmtiEnv &jvmti, JNIEnv &jni, jarray array, string signature) {
    // TODO
    string as_string = "[not implemented yet]";

    Object *ret = new Object(Type::from(jvmti, jni, signature), as_string);
    return unique_ptr<Object>(ret);
}

unique_ptr<Object> Object::fromDummy(jvmtiEnv &jvmti, JNIEnv &jni, string signature, string as_string) {
    Object *ret = new Object(Type::from(jvmti, jni, signature), as_string);
    return unique_ptr<Object>(ret);
}

unique_ptr<Object> Object::fromNothingTest(jvmtiEnv &jvmti, JNIEnv &jni, jobject object) {
    // TODO
    if(object == nullptr) {
            string signature = "Object";
            string as_string = "null";
            Object *ret = new Object(Type::from(jvmti, jni, signature), as_string);
            return unique_ptr<Object>(ret);
    }
    string signature = "Object";
    string as_string = "TODO";
    Object *ret = new Object(Type::from(jvmti, jni, signature), as_string);
    return unique_ptr<Object>(ret);
/*(jobject) nullptr
    jclass type = get_object_class(jni, object);

    jobject result = call_method(jni, object, "toString", "()Ljava/lang/String;");
    string as_string = (result == nullptr) ? "" : jeff::to_string(jni, static_cast<jstring>(result));

    std::string signature = get_class_signature(jvmti, type);
    Object *ret = new Object(Type::from(jvmti, jni, signature), as_string);
    jni.DeleteLocalRef(type);
    return unique_ptr<Object>(ret);*/
}

unique_ptr<Object> Object::from(jvmtiEnv &jvmti, JNIEnv &jni, jobject object) {
    if(object == nullptr) {
            string signature = "Object";
            string as_string = "null";
            Object *ret = new Object(Type::from(jvmti, jni, signature), as_string);
            return unique_ptr<Object>(ret);
    }
    
    jclass type = get_object_class(jni, object);

    jobject result = call_method(jni, object, "toString", "()Ljava/lang/String;");
    string as_string = (result == nullptr) ? "" : jeff::to_string(jni, static_cast<jstring>(result));

    std::string signature = get_class_signature(jvmti, type);
    
    // rmtbckp TODO: use instead jvmti.GetClassFields and iterate over all fields
    // Note the "Only directly declared fields are returned (not inherited fields)".
    // May need to call getSuperclass(), e.g. jmethodID mid_getName = jni.GetMethodID(cls, "getSuperclass", "()Ljava/lang/String;");
    string str2 ("Lcom/rmtbckp/sample/Main$Pet;");
    if (str2.compare(signature) == 0) {
        //printf("AAAAAAAAAAAAAAAAAAAAAAAAAA\n");
        jfieldID fidInt = jni.GetFieldID(type, "age", "I");
        jint iVal = jni.GetIntField(object, fidInt);
        //printf(", age = %d", iVal);
        as_string += (format(",\n\t\t\tage = %s") % iVal).str();
        
        
        fidInt = jni.GetFieldID(type, "weight", "I");
        iVal = jni.GetIntField(object, fidInt);
        //printf(", weight = %d", iVal);
        as_string += (format(",\n\t\t\tweight = %s") % iVal).str();
    }
    //
    Object *ret = new Object(Type::from(jvmti, jni, signature), as_string);
    jni.DeleteLocalRef(type);
    return unique_ptr<Object>(ret);
}

unique_ptr<Object> Object::from(jvmtiEnv &jvmti, JNIEnv &jni, bool value) {
    return unique_ptr<Object>(new Object(Type::from(jvmti, jni, 'Z'), (value == 0) ? "false" : "true"));
}

unique_ptr<Object> Object::from(jvmtiEnv &jvmti, JNIEnv &jni, jchar value) {
    return unique_ptr<Object>(new Object(Type::from(jvmti, jni, 'C'), std::to_string(value)));
}

unique_ptr<Object> Object::from(jvmtiEnv &jvmti, JNIEnv &jni, jbyte value) {
    return unique_ptr<Object>(new Object(Type::from(jvmti, jni, 'B'), std::to_string(value)));
}

unique_ptr<Object> Object::from(jvmtiEnv &jvmti, JNIEnv &jni, jshort value) {
    return unique_ptr<Object>(new Object(Type::from(jvmti, jni, 'S'), std::to_string(value)));
}

unique_ptr<Object> Object::from(jvmtiEnv &jvmti, JNIEnv &jni, jint value) {
    return unique_ptr<Object>(new Object(Type::from(jvmti, jni, 'I'), std::to_string(value)));
}

unique_ptr<Object> Object::from(jvmtiEnv &jvmti, JNIEnv &jni, jlong value) {
    return unique_ptr<Object>(new Object(Type::from(jvmti, jni, 'J'), std::to_string(value)));
}

unique_ptr<Object> Object::from(jvmtiEnv &jvmti, JNIEnv &jni, jfloat value) {
    return unique_ptr<Object>(new Object(Type::from(jvmti, jni, 'F'), std::to_string(value)));
}

unique_ptr<Object> Object::from(jvmtiEnv &jvmti, JNIEnv &jni, jdouble value) {
    return unique_ptr<Object>(new Object(Type::from(jvmti, jni, 'D'), std::to_string(value)));
}