#import <Foundation/Foundation.h>
@import Mantle;

@protocol AMQEncoding <NSObject>
- (nonnull NSData *)amqEncoded;
@end

@protocol AMQFieldValue <NSObject>
- (nonnull NSData *)amqFieldValueType;
@end

@interface AMQOctet : MTLModel<AMQEncoding>
- (nonnull instancetype)init:(char)octet;
@end

@interface AMQBit : MTLModel<AMQEncoding>
- (nonnull instancetype)init:(char)bit;
@end

@interface AMQBoolean : MTLModel<AMQEncoding,AMQFieldValue>
@property (nonatomic, readonly) BOOL boolValue;
- (nonnull instancetype)init:(BOOL)boolean;
@end

@interface AMQShort : MTLModel<AMQEncoding,AMQFieldValue>
- (nonnull instancetype)init:(NSUInteger)val;
@end

@interface AMQLong : MTLModel<AMQEncoding,AMQFieldValue>
- (nonnull instancetype)init:(NSUInteger)val;
@end

@interface AMQLonglong : MTLModel<AMQEncoding,AMQFieldValue>
- (nonnull instancetype)init:(NSUInteger)val;
@end

@interface AMQShortstr : MTLModel<AMQEncoding,AMQFieldValue>
@property (nonnull, nonatomic, copy, readonly) NSString *stringValue;
- (nonnull instancetype)init:(nonnull NSString *)string;
@end

@interface AMQLongstr : MTLModel<AMQEncoding,AMQFieldValue>
@property (nonnull, nonatomic, copy, readonly) NSString *stringValue;
- (nonnull instancetype)init:(nonnull NSString *)string;
@end

@interface AMQTable : MTLModel<AMQEncoding,AMQFieldValue>
- (nonnull instancetype)init:(nonnull NSDictionary *)dictionary;
@end

@interface AMQFieldValuePair : MTLModel<AMQEncoding>
- (nonnull instancetype)initWithFieldName:(nonnull NSString *)fieldName
                               fieldValue:(nonnull id <AMQEncoding,AMQFieldValue>)fieldValue;
@end

@interface AMQCredentials : AMQLongstr
- (nonnull instancetype)initWithUsername:(nonnull NSString *)username
                                password:(nonnull NSString *)password;
@end

@protocol AMQReplyContext <NSObject>
- (nonnull AMQCredentials *)credentials;
@end

@protocol AMQMethod <NSObject>
@property (nonnull, nonatomic, readwrite) NSArray *frameArguments;
+ (nonnull NSNumber *)classID;
+ (nonnull NSNumber *)methodID;
@end

@protocol AMQOutgoing <NSObject>
- (nonnull Class)expectedResponseClass;

@optional
- (nonnull id<AMQOutgoing,AMQMethod>)nextRequest;
@end

@protocol AMQIncoming <NSObject,AMQMethod>
- (nonnull id<AMQOutgoing,AMQMethod>)replyWithContext:(nonnull id<AMQReplyContext>)context;
@end

@interface AMQFrame : NSObject<AMQEncoding>
- (nonnull instancetype)initWithType:(nonnull NSNumber *)frame
                           channelID:(nonnull NSNumber *)channelID
                              method:(nonnull id <AMQMethod>)method;
@end

@interface AMQMethodPayload : NSObject<AMQEncoding>
- (nonnull instancetype)initWithClassID:(nonnull NSNumber *)classID
                               methodID:(nonnull NSNumber *)methodID
                              arguments:(nonnull NSArray *)arguments;
@end