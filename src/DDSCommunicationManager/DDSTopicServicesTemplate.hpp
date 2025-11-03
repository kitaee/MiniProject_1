#pragma once
#include "DDSServiceProvider.h"
#include <functional>

class DDSProviderInterface
{
public:
	virtual void injectDDSProvider(DDSServiceProvider* ddsServiceProvider) = 0;
	virtual bool create() = 0;
	virtual bool createDataReader(std::string qosLibName, std::string topicProfile, std::string readerProfile) = 0;
	virtual bool createDataWriter(std::string qosLibName, std::string topicProfile, std::string writerProfile) = 0;
	virtual bool createDataReaderWriter(std::string qosLibName, std::string topicProfile, std::string readerProfile, std::string writerProfile) = 0;
};

template <typename TTypeSupport, typename TDataWriter, typename TDataReader, typename TSeq, typename TTopicInstance>
class DDSTopicServicesTemplate : public DDSProviderInterface, public DDSDataReaderListener
{
public:
	DDSTopicServicesTemplate(DDSDomainParticipant* domainParticipant, DDSPublisher* publisher, DDSSubscriber* subscriber, std::string topicName);
	virtual ~DDSTopicServicesTemplate() = default;

public:
	TTopicInstance* createTopic();
	void createTopicServices();
	bool writeTopic(TTopicInstance* topicInstance);
	void injectDDSMsgProcessor(std::function<void(byte*)> msgProc);

	// inherited function (TopicDataInteface)
	virtual void injectDDSProvider(DDSServiceProvider* ddsServiceProvider) override;
	virtual bool create() override;
	virtual bool createDataReader(std::string qosLibName, std::string topicProfile, std::string readerProfile) override;
	virtual bool createDataWriter(std::string qosLibName, std::string topicProfile, std::string writerProfile) override;
	virtual bool createDataReaderWriter(std::string qosLibName, std::string topicProfile, std::string readerProfile, std::string writerProfile) override;

	// inherited function (DDSDataReaderListener)
	virtual void on_requested_deadline_missed(DDSDataReader* reader, const DDS_RequestedDeadlineMissedStatus& status) {}
	virtual void on_requested_incompatible_qos(DDSDataReader* reader, const DDS_RequestedIncompatibleQosStatus& status) {}
	virtual void on_sample_rejected(DDSDataReader* reader, const DDS_SampleRejectedStatus& status) {}
	virtual void on_liveliness_changed(DDSDataReader* reader, const DDS_LivelinessChangedStatus& status) {}
	virtual void on_data_available(DDSDataReader* reader) override;
	virtual void on_subscription_matched(DDSDataReader* reader, const DDS_SubscriptionMatchedStatus& status) {}
	virtual void on_sample_lost(DDSDataReader* reader, const DDS_SampleLostStatus& status) {}

private:
	DDSTopicServicesTemplate() = default;

private:
	TDataWriter* dataWriter;
	TDataReader* dataReader;
	std::string topicName;
	DDSServiceProvider* dcps;
	DDSDomainParticipant* domainParticipant;
	DDSPublisher* publisher;
	DDSSubscriber* subscriber;
	DDSDataWriter* dataWriterVar;
	DDSDataReader* dataReaderVar;
	DDSTypeSupport* typeSupport;
	std::function<void(byte*)> msgProcCallback;
	DDSServiceProvider* ddsServiceProvider;
};

/************************************************************************
	constructor / destructor = default
************************************************************************/
template <typename TTypeSupport, typename TDataWriter, typename TDataReader, typename TSeq, typename TTopicInstance>
DDSTopicServicesTemplate<TTypeSupport, TDataWriter, TDataReader, TSeq, TTopicInstance>
::DDSTopicServicesTemplate(DDSDomainParticipant* domainParticipant, DDSPublisher* publisher, DDSSubscriber* subscriber, std::string topicName)
{
	dataWriter = nullptr;
	dataReader = nullptr;
	this->domainParticipant = domainParticipant;
	this->publisher = publisher;
	this->subscriber = subscriber;
	this->topicName = topicName;
}

/************************************************************************
	implement how topic registration and distribution should be handled.
************************************************************************/
template <typename TTypeSupport, typename TDataWriter, typename TDataReader, typename TSeq, typename TTopicInstance>
TTopicInstance*
DDSTopicServicesTemplate<TTypeSupport, TDataWriter, TDataReader, TSeq, TTopicInstance>::createTopic()
{
	TTopicInstance* topic = new TTopicInstance;
	return topic;
}

template <typename TTypeSupport, typename TDataWriter, typename TDataReader, typename TSeq, typename TTopicInstance>
void
DDSTopicServicesTemplate<TTypeSupport, TDataWriter, TDataReader, TSeq, TTopicInstance>::createTopicServices()
{
	std::string typeName = TTypeSupport::get_type_name();
	TTypeSupport::register_type(domainParticipant, typeName.c_str());

	ddsServiceProvider->createTopic(topicName, typeName);

	dataWriterVar = ddsServiceProvider->createWriter();
	dataWriter = TDataWriter::narrow(dataWriterVar);

	ddsServiceProvider->registerReaderListener(this);
	dataReaderVar = ddsServiceProvider->createReader();
	dataReaderVar->set_listener(this, DDS_DATA_AVAILABLE_STATUS | DDS_REQUESTED_DEADLINE_MISSED_STATUS);
}

template <typename TTypeSupport, typename TDataWriter, typename TDataReader, typename TSeq, typename TTopicInstance>
bool
DDSTopicServicesTemplate<TTypeSupport, TDataWriter, TDataReader, TSeq, TTopicInstance>::writeTopic(TTopicInstance* topicInstance)
{
	bool isCompleted = false;
	if (dataWriter != nullptr)
	{
		isCompleted = dataWriter->write(*topicInstance, DDS_HANDLE_NIL);
	}
	else;

	return isCompleted;
}

template <typename TTypeSupport, typename TDataWriter, typename TDataReader, typename TSeq, typename TTopicInstance>
void
DDSTopicServicesTemplate<TTypeSupport, TDataWriter, TDataReader, TSeq, TTopicInstance>::injectDDSMsgProcessor(std::function<void(byte*)> msgProc)
{
	msgProcCallback = msgProc;
}


/************************************************************************
	inherited function - implementation to create the topic
************************************************************************/
template <typename TTypeSupport, typename TDataWriter, typename TDataReader, typename TSeq, typename TTopicInstance>
void
DDSTopicServicesTemplate<TTypeSupport, TDataWriter, TDataReader, TSeq, TTopicInstance>::injectDDSProvider(DDSServiceProvider* ddsServiceProvider)
{
	this->ddsServiceProvider = ddsServiceProvider;
}

template <typename TTypeSupport, typename TDataWriter, typename TDataReader, typename TSeq, typename TTopicInstance>
bool
DDSTopicServicesTemplate<TTypeSupport, TDataWriter, TDataReader, TSeq, TTopicInstance>::create()
{
	createTopicServices();
	return true;
}

template <typename TTypeSupport, typename TDataWriter, typename TDataReader, typename TSeq, typename TTopicInstance>
bool
DDSTopicServicesTemplate<TTypeSupport, TDataWriter, TDataReader, TSeq, TTopicInstance>::createDataReader(std::string qosLibName, std::string topicProfile, std::string readerProfile)
{
	bool result = false;

	std::string typeName = TTypeSupport::get_type_name();
	TTypeSupport::register_type(domainParticipant, typeName.c_str());

	ddsServiceProvider->createTopic(topicName, typeName);

	ddsServiceProvider->registerReaderListener(this);
	dataReaderVar = ddsServiceProvider->createReader();

	if (dataReaderVar != nullptr)
	{
		dataReaderVar->set_listener(this, DDS_DATA_AVAILABLE_STATUS | DDS_REQUESTED_DEADLINE_MISSED_STATUS);
		result = true;
	}
	else;

	return result;
}

template <typename TTypeSupport, typename TDataWriter, typename TDataReader, typename TSeq, typename TTopicInstance>
bool
DDSTopicServicesTemplate<TTypeSupport, TDataWriter, TDataReader, TSeq, TTopicInstance>::createDataWriter(std::string qosLibName, std::string topicProfile, std::string writerProfile)
{
	bool result = false;

	std::string typeName = TTypeSupport::get_type_name();
	TTypeSupport::register_type(domainParticipant, typeName.c_str());

	ddsServiceProvider->createTopic(topicName, typeName);

	dataWriterVar = ddsServiceProvider->createWriter();

	if (dataWriterVar != nullptr)
	{
		dataWriter = TDataWriter::narrow(dataWriterVar);
		result = true;
	}
	else;

	return result;
}

template <typename TTypeSupport, typename TDataWriter, typename TDataReader, typename TSeq, typename TTopicInstance>
bool
DDSTopicServicesTemplate<TTypeSupport, TDataWriter, TDataReader, TSeq, TTopicInstance>::createDataReaderWriter(std::string qosLibName, std::string topicProfile, std::string readerProfile, std::string writerProfile)
{
	bool result = false;

	std::string typeName = TTypeSupport::get_type_name();
	TTypeSupport::register_type(domainParticipant, typeName.c_str());

	ddsServiceProvider->createTopic(topicName, typeName);

	dataWriterVar = ddsServiceProvider->createWriter();

	ddsServiceProvider->registerReaderListener(this);
	dataReaderVar = ddsServiceProvider->createReader();

	if (dataWriterVar != nullptr && dataReaderVar != nullptr)
	{
		dataWriter = TDataWriter::narrow(dataWriterVar);

		dataReaderVar->set_listener(this, DDS_DATA_AVAILABLE_STATUS | DDS_REQUESTED_DEADLINE_MISSED_STATUS);

		result = true;
	}
	else;

	return result;
}

/************************************************************************
	inherited function - implementation to process the topic data
************************************************************************/
template <typename TTypeSupport, typename TDataWriter, typename TDataReader, typename TSeq, typename TTopicInstance>
void
DDSTopicServicesTemplate<TTypeSupport, TDataWriter, TDataReader, TSeq, TTopicInstance>::on_data_available(DDSDataReader* reader)
{
	TDataReader* dataReader;
	dataReader = TDataReader::narrow(reader);

	if (dataReader)
	{
		DDS_ReturnCode_t retCode;
		TSeq seqList;
		DDS_SampleInfoSeq infoSeq;

		//retCode = dataReader->read(seqList, infoSeq, DDS_LENGTH_UNLIMITED, DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);
		retCode = dataReader->take(seqList, infoSeq, DDS_LENGTH_UNLIMITED, DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);

		if (retCode == DDS_RETCODE_OK)
		{
			for (unsigned int i = 0; i < seqList.length(); i++)
			{
				if (infoSeq[i].valid_data)
				{
					byte* data = new byte[sizeof(TTopicInstance)];
					memcpy(data, &seqList[i], sizeof(TTopicInstance));

					msgProcCallback(data);

					delete[] data;
				}
			}
		}
		else
		{
			std::cerr << retCode << ": Reading data error." << std::endl;
		}

		retCode = dataReader->return_loan(seqList, infoSeq);
	}
	else
	{
		std::cerr << "DataReader internal error." << std::endl;
	}
}